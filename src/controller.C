#include "controller.H"


controller::controller() {
}

controller::controller(const controller& orig) {
}

controller::~controller() {
}

void controller::setMenuList(vector<menu*>* menuList) {
	for(int i = 0; i < menuList->size(); i++) {
		this->menuList.push_back(menuList->at(i));
	}
	this->setCurrentMenu(0);
}

void controller::setCurrentMenu(int option) { currentMenu = *this->getMenu(option); }

// TODO: This
void controller::checkUserInput() {

}
