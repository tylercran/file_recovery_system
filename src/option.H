/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   option.H
 * Author: jeff
 *
 * Created on November 11, 2018, 6:43 PM
 */

#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <iostream>
#include "viewable.H"
#include "selectable.H"

using namespace std;

class option : public viewable, public selectable {
public:
    option();
    option(const option& orig);
    virtual ~option();
        
    void   toString() override;
    
    //get and set
    string getText()               { return text; }
    void   setText(string optText) { text = optText; }
    
    //selected
    void selected() override;
    
private:
    
    string    text;
    viewable* toDisplay;
    viewable* toDo;
        
};

#endif /* OPTION_H */

