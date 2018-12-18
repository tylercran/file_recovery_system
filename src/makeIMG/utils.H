#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <limits>

using namespace std;

bool dir_exists(const char*);
int  getInt_range(int min, int max);

#endif /* UTILS_H */

