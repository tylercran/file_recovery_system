/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menu.C
 * Author: jeff
 * 
 * Created on November 10, 2018, 1:03 PM
 */

#include "menu.H"
#include <iostream>

menu::menu() {
}

menu::menu(const menu& orig) {
}

menu::~menu() {
}

void menu::printOptionsList() {
    for(int i = 1; i < options.size(); i++) {
        cout << this->options.at(i)->getText();
    }

    cout << options[0]->getText();
}

void menu::toString(){

    int cnt = 0;
    cout << this->title << endl;
    for(auto i : this->options)
    {
       cout << ++cnt << ". ";
       i->toString();
       cout << endl;
    }
    cout << endl;

}

void menu::select(){
}

