#include <iostream>
#include <sys/syscall.h>
#include "FileSystem.h"
#include "Path.h"

// Added Path &path to all other list functions and added a recursive call in the last list call for directories.
// Also setGivenPath in Path

int main(int argc, char *argv[]) {

    FileSystem image(argv[1]);

    image.init();

    Path path(argv[2]);

    image.list(path, 0, false);

    printf("\nDeleted Entries\n");

    image.list(path, 0, true);
    printf("\n\n");

    vector<Entry> deletedEntries = image.getEntries(2, NULL, NULL, true);

    cout << "Would you like to shutdown after you the program has recovered the files? (Y/N)\n";

    char choice;
    cin >> choice;

    if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        do {
            cout << "Please enter Y or N.\n";
            cin >> choice;
        } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
    }

    image.confirmUndelete(deletedEntries);

    if(choice == 'y' || choice == 'Y') {
        system("shutdown now");
    }
    if(choice == 'n' || choice == 'N') {
        cout << "I guess we need to close now.";
    }

    return 999;
}