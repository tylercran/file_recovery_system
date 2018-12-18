//
// Created by ty on 12/11/18.
//

#ifndef ENTRY_H
#define ENTRY_H

#include <string>

using namespace std;

// Size of a  entry
#define ENTRY_SIZE         0x20

// Offsets
#define SHORTNAME           0x00
#define ATTRIBUTES          0x0b
#define CLUSTER_LOW         0x1a
#define CLUSTER_HIGH        0x14
#define FILESIZE            0x1c

// Attributes
#define ATTRIBUTES_HIDE     (1<<1)
#define ATTRIBUTES_DIR      (1<<4)
#define ATTRIBUTES_LONGFILE (0xf)
#define ATTRIBUTES_FILE     (0x20)

// Prefix used for erased files
#define ERASED                  0xe5

class Entry {
public:
    Entry();

    string getFilename();
    bool isDirectory();
    bool isHidden();
    bool isDeleted();

    string shortName;
    string longName;
    char attributes;
    unsigned int cluster;
    unsigned long long size;

    void updateData();
    void setData(string data);
    long long address;
    bool hasData;
    string data;

    bool isCorrect();
    bool isZero();

    bool printable(unsigned char c);
};


#endif // ENTRY_H
