#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>
#include "Path.h"
#include "Entry.h"

using namespace std;

// Last cluster
#define LAST (-1)

// Header offsets
#define BYTES_PER_SECTOR        0x0b
#define SECTORS_PER_CLUSTER     0x0d
#define RESERVED_SECTORS        0x0e
#define S                       0x10
#define TOTAL_SECTORS           0x20
#define SECTORS_PER_            0x24
#define ROOT_DIRECTORY          0x2c
#define DISK_LABEL              0x47
#define DISK_LABEL_SIZE         11
#define DISK_OEM                0x3
#define DISK_OEM_SIZE           8
#define DISK_FS                 0x52
#define DISK_FS_SIZE            8

#define FAT32                   0


class FileSystem {

public:
    FileSystem(string userImage);

    bool init();

    void parseHeader();

    int readData(unsigned long long address, char *buffer, int size);

    unsigned long long clusterAddress(unsigned int cluster, bool isRoot = NULL);

    bool validCluster(unsigned int cluster);

    vector<Entry> getEntries(unsigned int cluster, int *clusters = NULL, bool *hasFree = NULL, bool deletedFlag = NULL);

    void list(vector<Entry> &entries, string curPath = "/", int depth = 0);
    void list(Path &path, int depth = 0, bool deletedFlag = NULL);
    void list(unsigned int cluster, string curPath = "/", int depth = 0, bool deletedFlag = NULL);

    bool findDirectory(Path &path, Entry &outputEntry);

    unsigned int nextCluster(unsigned int cluster, int fat=0);

    vector<Entry> getDeletedList();
    void listDeletedEntries();

    void confirmUndelete(vector<Entry> entries);
    void undelete(Entry entry);

private:
    string imageName;
    unsigned long offset;
    int file;

    bool writeMode;

    // Header values
    int type;
    string diskLabel;
    string oemName;
    string fsType;
    unsigned long long numSectors;
    unsigned long long sectorBytes;
    unsigned long long numSectorsInCluster;
    unsigned long long reservedSectors;
    unsigned long long s;
    unsigned long long sectorsPer;
    unsigned long long rootDirectory;
    unsigned long long strange;
    unsigned int bits;

    // Computed values
    unsigned long long start;
    unsigned long long dataStart;
    unsigned long long bytesPerCluster;
    unsigned long long totalSize;
    unsigned long long dataSize;
    unsigned long long Size;
    unsigned long long totalClusters;

    unsigned long long rootClusters;

    // Stats values
    bool statsComputed;
    unsigned long long freeClusters;

    vector<Entry> deletedEntries;


};

#endif // FILESYSTEM_H