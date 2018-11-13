#include "controller.H"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

controller::controller() {
}

controller::controller(const controller& orig) {
}

controller::~controller() {
}

void controller::checkUserInput() {
	int userInputInt;
	double userInputDouble;
	while(true) {
		currentMenu.printOptionsList();
		// printf("\nEnter your option:\n");
		// scanf("%lf", &userInputDouble);
		// userInputInt = (int)floor(userInputDouble);

		while(userInputInt < 0 || userInputInt > currentMenu.getNumOptions()) {
			printf("Please enter a number between 0 and %d.", currentMenu.getNumOptions());
			//scanf("%lf", &userInputDouble);
			cin >> userInputDouble;
			while(cin.fail()) {
				cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				printf("Enter a number");
			}
			userInputInt = (int)floor(userInputDouble);
		}
		if(userInputInt == 0) {
			printf("Invalid Menu Number and Option combination. Exiting program.\n");
			exit(-1);
		}
		else {
			previousMenu = currentMenu;
			this->setCurrentMenu(userInputInt);
		}
	}
}
