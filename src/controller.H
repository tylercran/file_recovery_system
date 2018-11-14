#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "menu.H"

using namespace std;

class controller {
public:

	controller();

	controller(const controller& orig);

	virtual ~controller();

	void checkUserInput();

	void setMenuList(vector<menu*>* menuList);
	void setCurrentMenu(int option);

	void setPrevious() { previousMenu = currentMenu; }

	menu* getMenu(int option) { return menuList.at(option); }


private:

	menu previousMenu;
	menu currentMenu;
	vector<menu*> menuList;

};

#endif /* CONTROLLER_H */