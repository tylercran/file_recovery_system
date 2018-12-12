#include <iostream>
#include "FileSystem.h"
#include "Path.h"

int main(int argc, char *argv[]) {

    FileSystem image(argv[1]);

    image.init();

    Path path(argv[2]);

    image.list(path);
}