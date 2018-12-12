#include <sstream>
#include "Path.h"
#include "Utils.h"

using namespace std;

Path::Path(string userPath) :givenPath(userPath) {
    split(givenPath, '/', previousDirs);
}

string Path::splitPreviousDirectory() {
    stringstream path(this->givenPath);
    string prevDir;
    while(getline(path, prevDir, '/')) {
        this->previousDirs.push_back(prevDir);
    }
}

string Path::getPreviousDirectory() {
    string dirPath = "";
    for(int i = 0; i < previousDirs.size() - 1; i++) {
        dirPath += previousDirs[i] + "/";
    }

    return dirPath;
}

string Path::getWantedDirectory() {
    return previousDirs[previousDirs.size() - 1];
}

string Path::getGivenPath() {
    return givenPath;
}

vector<string> Path::getPreviousDirs(){
    return previousDirs;
}