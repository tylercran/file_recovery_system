//
// Created by ty on 12/9/18.
//
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <set>

#include "Utils.h"
#include "FileSystem.h"
#include "Path.h"
#include "Entry.h"
#include "File.h"

FileSystem::FileSystem(string userImage):imageName(userImage){
    file = open(imageName.c_str(), O_RDONLY | O_LARGEFILE);
}

bool FileSystem::init() {
    // Parsing header
    parseHeader();

    // Computing values
    start = sectorBytes * reservedSectors;
    dataStart = start + s * sectorsPer * sectorBytes;
    bytesPerCluster = sectorBytes * numSectorsInCluster;
    totalSize = numSectors * sectorBytes;
    Size = sectorsPer * sectorBytes;
    totalClusters = (Size * 8) / bits;
    dataSize = totalClusters * bytesPerCluster;

    return strange == 0;
}

void FileSystem::parseHeader() {
    char buffer[64];

    readData(0x0, buffer, sizeof(buffer));
    sectorBytes = 512;
    // For FAT32, this is going to be 64 if the drive is smaller than 2tb, 32 if it's smaller than 32 gb, 16 if it's
    // smaller than 16 gb, 8 if it's smaller than 8gb, and 1 if it's smaller than 260MB.
    numSectorsInCluster = buffer[SECTORS_PER_CLUSTER] & 0xff;
    reservedSectors = READ_SHORT(buffer, RESERVED_SECTORS) & 0xffff;
//    oemName = string(buffer + DISK_OEM, DISK_OEM_SIZE);
    s = buffer[S];

    type = 32;
    bits = 32;
    sectorsPer = READ_LONG(buffer, SECTORS_PER_) & 0xffffffff;
    numSectors = READ_LONG(buffer, TOTAL_SECTORS) & 0xffffffff;
    diskLabel = string(buffer + DISK_LABEL, DISK_LABEL_SIZE);
    rootDirectory = READ_LONG(buffer, ROOT_DIRECTORY) & 0xffffffff;
    fsType = string(buffer + DISK_FS, DISK_FS_SIZE);

    if (sectorBytes != 512) {
        printf("WARNING: Bytes per sector is not 512 (%llu)\n", sectorBytes);
        strange++;
    }

    if (numSectorsInCluster > 128) {
        printf("WARNING: Sectors per cluster high (%llu)\n", numSectorsInCluster);
        strange++;
    }

    if (s != 2) {
        printf("WARNING: s number different of 2 (%llu)\n", s);
        strange++;
    }

    if (rootDirectory != 2 && type == 32) {
        printf("WARNING: Root directory is not 2 (%llu)\n", rootDirectory);
        strange++;
    }
}

// Can't really change this one.
int FileSystem::readData(unsigned long long address, char *buffer, int size) {
    if (totalSize != -1 && address + size > totalSize) {
        cerr << "! Trying to read outside the disk" << endl;
    }

    // Move the pointer in the file to the correct location.
    lseek64(file, offset + address, SEEK_SET);

    int n;
    int pos = 0;
    do {
        // Read a file starting at buffer + position on a file of size size.
        n = read(file, buffer + pos, size);
        // Change the positions of position and size.
        if (n > 0) {
            pos += n;
            size -= n;
        }
    } while ((size > 0) && (n > 0));

    return n;
}

void FileSystem::list(vector<Entry> &entries)
{
    vector<Entry>::iterator it;

    for (it=entries.begin(); it!=entries.end(); it++) {
        Entry &entry = *it;

//        if (entry.isDeleted()) {
//            continue;
//        }

        if(entry.isDeleted()) {
            printf("\nNext is deleted. \n");
        }
        if (entry.isDirectory()) {
            printf("d");
        } else {
            printf("f");
        }

        string name = entry.getFilename();
        if (entry.isDirectory()) {
            name += "/";
        }

        printf(" %-30s", name.c_str());

        printf(" c=%u", entry.cluster);

        if (!entry.isDirectory()) {
            string pretty = prettySize(entry.size);
            printf(" s=%llu (%s)", entry.size, pretty.c_str());
        }

        if (entry.isHidden()) {
            printf(" h");
        }

        if(entry.isDeleted()) {
            printf("\n");
        }

        printf("\n");
        fflush(stdout);
    }
}

unsigned long long FileSystem::clusterAddress(unsigned int cluster, bool isRoot)
{
    if (type == FAT32 || !isRoot) {
        cluster -= 2;
    }

    unsigned long long addr = (dataStart + sectorBytes*numSectorsInCluster*cluster);

    return addr;
}

bool FileSystem::validCluster(unsigned int cluster)
{
    return cluster < totalClusters;
}

vector<Entry> FileSystem::getEntries(unsigned int cluster, int *clusters, bool *hasFree)
{
    bool isRoot = false;
    bool contiguous = false;
    int foundEntries = 0;
    int badEntries = 0;
    bool isValid = false;
    set<unsigned int> visited;
    vector<Entry> entries;
    File filename;

    if (clusters != NULL) {
        *clusters = 0;
    }

    if (hasFree != NULL) {
        *hasFree = false;
    }

    if (cluster == 0 && type == FAT32) {
        cluster = rootDirectory;
    }

    isRoot = (type==0 && cluster==rootDirectory);

    if (cluster == rootDirectory) {
        isValid = true;
    }

    if (!validCluster(cluster)) {
        return vector<Entry>();
    }

    do {
        bool localZero = false;
        int localFound = 0;
        int localBadEntries = 0;
        unsigned long long address = clusterAddress(cluster, isRoot);
        char buffer[ENTRY_SIZE];
        if (visited.find(cluster) != visited.end()) {
            cerr << "! Looping directory" << endl;
            break;
        }
        visited.insert(cluster);

        unsigned int i;
        for (i=0; i<bytesPerCluster; i+=sizeof(buffer)) {
            // Reading data
            readData(address, buffer, sizeof(buffer));

            // Creating entry
            Entry entry;

            entry.attributes = buffer[ATTRIBUTES];
            entry.address = address;

            if (entry.attributes == ATTRIBUTES_LONGFILE) {
                // Long file part
                filename.append(buffer);
            } else {
                entry.shortName = string(buffer, 11);
                entry.longName = filename.getFilename();
                entry.size = READ_LONG(buffer, FILESIZE)&0xffffffff;
                entry.cluster = (READ_SHORT(buffer, CLUSTER_LOW)&0xffff) | (READ_SHORT(buffer, CLUSTER_HIGH)<<16);
                entry.setData(string(buffer, sizeof(buffer)));

                if (!entry.isZero()) {
                    if (entry.isCorrect() && validCluster(entry.cluster)) {
                        entries.push_back(entry);
                        localFound++;
                        foundEntries++;

                        if (!isValid && entry.getFilename() == "." && entry.cluster == cluster) {
                            isValid = true;
                        }
                    } else {
                        localBadEntries++;
                        badEntries++;
                    }

                    localZero = false;
                } else {
                    localZero = true;
                }
            }

            address += sizeof(buffer);
        }

        int previousCluster = cluster;

        if (isRoot) {
            if (cluster+1 < rootClusters) {
                cluster++;
            } else {
                cluster = LAST;
            }
        } else {
            cluster = nextCluster(cluster);
        }

        if (clusters) {
            (*clusters)++;
        }

        if (cluster == 0 || contiguous) {
            contiguous = true;

            if (hasFree != NULL) {
                *hasFree = true;
            }
            if (!localZero && localFound && localBadEntries<localFound) {
                cluster = previousCluster+1;
            } else {
                if (!localFound && clusters) {
                    (*clusters)--;
                }
                break;
            }
        }

        if (!isValid) {
            if (badEntries>foundEntries) {
                cerr << "! Entries don't look good, this is maybe not a directory" << endl;
                return vector<Entry>();
            }
        }
    } while (cluster != LAST);

    return entries;
}


void FileSystem::list(Path &path)
{
    Entry entry;

    if (findDirectory(path, entry)) {
        list(entry.cluster);
    }
}

void FileSystem::list(unsigned int cluster)
{
    bool hasFree = false;
    vector<Entry> entries = getEntries(cluster, NULL, &hasFree);
    printf("Directory cluster: %u\n", cluster);
    if (hasFree) {
        printf("Warning: this directory has free clusters that was read contiguously\n");
    }
    list(entries);
}

bool FileSystem::findDirectory(Path &path, Entry &outputEntry)
{
    int cluster;
    vector<string> parts = path.getPreviousDirs();
    cluster = rootDirectory;
    outputEntry.cluster = cluster;

    for (int i=0; i<parts.size(); i++) {
        if (parts[i] != "") {
            parts[i] = strtolower(parts[i]);
            vector<Entry> entries = getEntries(cluster);
            vector<Entry>::iterator it;
            bool found = false;

            for (it=entries.begin(); it!=entries.end(); it++) {
                Entry &entry = *it;
                string name = entry.getFilename();
                if (entry.isDirectory() && strtolower(name) == parts[i]) {
                    outputEntry = entry;
                    cluster = entry.cluster;
                    found = true;
                }
            }

            if (!found) {
                cerr << "Error: directory " << path.getGivenPath() << " not found" << endl;
                return false;
            }
        }
    }

    return true;
}

unsigned int FileSystem::nextCluster(unsigned int cluster, int fat)
{
    int bytes = (bits == 32 ? 4 : 2);
    char buffer[bytes];

    if (!validCluster(cluster)) {
        return 0;
    }

    readData(start+dataSize*fat+(bits*cluster)/8, buffer, sizeof(buffer));

    unsigned int next;

    if (type == FAT32) {
        next = READ_LONG(buffer, 0)&0x0fffffff;

        if (next >= 0x0ffffff0) {
            return LAST;
        } else {
            return next;
        }
    } else {
        next = READ_SHORT(buffer,0)&0xffff;

        if (bits == 12) {
            int bit = cluster*bits;
            if (bit%8 != 0) {
                next = next >> 4;
            }
            next &= 0xfff;
            if (next >= 0xff0) {
                return LAST;
            } else {
                return next;
            }
        } else {
            if (next >= 0xfff0) {
                return LAST;
            } else {
                return next;
            }
        }
    }
}