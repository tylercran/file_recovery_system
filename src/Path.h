#ifndef PATH_H
#define PATH_H

#include <string>
#include <vector>

using namespace std;

class Path {
public:
    Path(string givenPath);

    string splitPreviousDirectory();

    string getPreviousDirectory();

    string getWantedDirectory();

    vector<string> getPreviousDirs();

    string getGivenPath();

    void setGivenPath(string addOn);

private:
    string givenPath;
    vector<string> previousDirs;
};

#endif // PATH_H