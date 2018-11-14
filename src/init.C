#include "init.H"
#include "controller.H"
#include "menu.H"
#include "option.H"
#include "selectable.H"
#include "utils.H"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

void init() {

	viewable* rootMenu = new menu();
	rootMenu = createMenu(rootTitleString());


	rootMenu->toString();

	// option* root_menu_option_0 = new option;
	// root_menu_option_0->setText("** 0 to close program.\n\n");

	// option* root_menu_option_1 = new option;
	// root_menu_option_1->setText("** 1: Recover all files from my drive.\n");

	// option* root_menu_option_2 = new option;
	// root_menu_option_2->setText("** 2: Specify a specific file type to restore.\n");

	// option* root_menu_option_3 = new option;
	// root_menu_option_3->setText("** 3: Compare files the operating system does not know about.\n");

	// option* root_menu_option_4 = new option;
	// root_menu_option_4->setText("** 4: Recover individual files.\n");

	// option* root_menu_option_5 = new option;
	// root_menu_option_5->setText("** 5: Repair a damaged drive.\n");

	// rootMenu->addOption(root_menu_option_0);
	// rootMenu->addOption(root_menu_option_1);
	// rootMenu->addOption(root_menu_option_2);
	// rootMenu->addOption(root_menu_option_3);
	// rootMenu->addOption(root_menu_option_4);
	// rootMenu->addOption(root_menu_option_5);

	// menu* menu1 = new menu;
	// menu1->setTitle("\n\n*************************************\n"
	// 	"** RECOVER ALL FILES FROM MY DRIVE **\n"
	// 	"*************************************\n\n"
	// 	"Choose an option.\n\n");

	// menu* menu2 = new menu;
	// menu2->setTitle("\n\n*********************************************\n"
	// 	"** SPECIFY A SPECIFIC FILE TYPE TO RESTORE **\n"
	// 	"*********************************************\n\n"
	// 	"Choose an option.\n\n");

	// menu* menu3 = new menu;
	// menu3->setTitle("\n\n************************************************************\n"
	// 	"** COMPARE FILES THE OPERATING SYSTEM DOES NOT KNOW ABOUT **\n"
	// 	"************************************************************\n\n"
	// 	"Choose an option.\n\n");

	// menu* menu4 = new menu;
	// menu4->setTitle("\n\n******************************\n"
	// 	"** RECOVER INDIVIDUAL FILES **\n"
	// 	"******************************\n\n"
	// 	"Choose an option.\n\n");

	// menu* menu5 = new menu;
	// menu5->setTitle("\n\n****************************\n"
	// 	"** REPAIR A DAMAGED DRIVE **\n"
	// 	"****************************\n\n"
	// 	"Choose an option.\n\n");

	// menu* menuWIP = new menu;
	// menuWIP->setTitle("\n\nWILL BE FINISHED AT ANOTHER TIME.\n");

	// option* childOption1 = new option;
	// option* childOption2 = new option;

	// childOption1->setText("** 1: Continue with recovery.\n");
	// childOption2->setText("** 2: Back to previous menu.\n");

	// menu1->addOption(root_menu_option_0);
	// menu1->addOption(childOption1);
	// menu1->addOption(childOption2);

	// menu2->addOption(root_menu_option_0);
	// menu2->addOption(childOption1);
	// menu2->addOption(childOption2);

	// menu3->addOption(root_menu_option_0);
	// menu3->addOption(childOption1);
	// menu3->addOption(childOption2);

	// menu4->addOption(root_menu_option_0);
	// menu4->addOption(childOption1);
	// menu4->addOption(childOption2);

	// menu5->addOption(root_menu_option_0);
	// menu5->addOption(childOption1);
	// menu5->addOption(childOption2);

	// menuWIP->addOption(new option);

	// vector<menu*>* menus = new vector<menu*>();

	// menus->push_back(rootMenu);
	// menus->push_back(menu1);
	// menus->push_back(menu2);
	// menus->push_back(menu3);
	// menus->push_back(menu4);
	// menus->push_back(menu5);
	// menus->push_back(menuWIP);

	// controller* myController = new controller();
	// myController->setMenuList(menus);
	// myController->checkUserInput();

	// delete rootMenu;
	// delete menu1;
	// delete menu2;
	// delete menu3;
	// delete menu4;
	// delete menu5;
	// delete menuWIP;
	// delete menus;

	// delete root_menu_option_0;
	// delete root_menu_option_1;
	// delete root_menu_option_2;
	// delete root_menu_option_3;
	// delete root_menu_option_4;
	// delete root_menu_option_5;
	// delete childOption1;
	// delete childOption2;
}
