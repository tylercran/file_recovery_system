//
// Created by ty on 12/11/18.
//

#include "Entry.h"

#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <iostream>
#include <string.h>

#include "Utils.h"

using namespace std;

Entry::Entry()
        : hasData(false),
          address(0)
{
}

void Entry::setData(string data_)
{
    hasData = true;
    data = data_;
}

void Entry::updateData()
{
    data[ATTRIBUTES] = attributes&0xff;
    WRITE_LONG(data, FILESIZE, size&0xffffffff);
    WRITE_SHORT(data, CLUSTER_LOW, cluster&0xffff);
    WRITE_SHORT(data, CLUSTER_HIGH, (cluster>>16)&0xffff);
}

string Entry::getFilename()
{
    if (longName != "") {
        return longName;
    } else {
        string name;
        string ext = trim(shortName.substr(8,3));
        string base = trim(shortName.substr(0,8));

        if (isDeleted()) {
            base = base.substr(1);
        }

        name = base;

        if (ext != "") {
            name += "." + ext;
        }

        return name;
    }
}

bool Entry::isDirectory()
{
    return attributes&ATTRIBUTES_DIR;
}

bool Entry::isHidden()
{
    return attributes&ATTRIBUTES_HIDE;
}

// Found the 0xe5 in the fragmentation section in the "Design ..." wiki
//
bool Entry::isDeleted() {
    return ((data[0])& 0xff) == 0xe5;
}

bool Entry::isZero()
{
    for (int i=0; i<data.size(); i++) {
        if (data[i] != 0) {
            return false;
        }
    }

    return true;
}

bool Entry::printable(unsigned char c)
{
    return isprint(c);
}

bool Entry::isCorrect()
{
    if (attributes && !(attributes&ATTRIBUTES_DIR) && !(attributes&ATTRIBUTES_FILE)) {
        return false;
    }

    if (isDirectory() && cluster == 0 && getFilename()!="..") {
        return false;
    }

    for (int i=1; i<11; i++) {
        if (printable(data[i])) {
            return true;
        }
    }

    return false;
}