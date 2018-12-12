//
// Created by ty on 12/9/18.
//

#ifndef FILE_H
#define FILE_H

#include <vector>
#include <string>

using namespace std;

/**
 * Special class to handle long file names
 */
class File
{
public:
    string getFilename();

    void append(char *buffer);

protected:
    string data;
    vector<string> letters;
};


#endif //FILE_H
