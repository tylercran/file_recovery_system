/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menu.H
 * Author: jeff
 *
 * Created on November 10, 2018, 1:03 PM
 */

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "viewable.H"
#include "option.H"
#include "selectable.H"

using namespace std;

class menu : public viewable{
public:
    //ctor
    menu();
    //alt ctor
    menu(const string title, vector<selectable*> options);
    //copy
    menu(const menu& orig);
    //dtor
    virtual ~menu();
    
    //print menu
    void toString() override;
    
    //select from menu
    void select();
    
    //getters
    int  getNumOptions() { return options.size(); }
    void printOptionsList();
    string getTitle() { return title; }
    
    //setters
    void setTitle(string toSet)  { title = toSet; }
    void addOption(option* toAdd) { options.push_back(toAdd); }
private:
    
    string title;
    vector<selectable*> options;
};

#endif /* MENU_H */