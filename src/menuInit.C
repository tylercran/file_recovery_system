#include "menuInit.H"

#include <string>

viewable* createMenu(string titleString) {
	menu* tempMenu = new menu();

	tempMenu->setTitle(titleString);

	viewable* returnMenu = tempMenu;

	return returnMenu;
}