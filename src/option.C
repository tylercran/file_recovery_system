/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   option.C
 * Author: jeff
 * 
 * Created on November 11, 2018, 6:43 PM
 */

#include "option.H"

option::option() {
}

option::option(string text) {
    this->text = text;
}

option::option(const option& orig) {
}

option::~option() {
}

//remove this
void option::printOptionsList(){
}

void option::toString(){
    cout << text; 
}

void option::selected(){
    ;
    //TODO Implement something like below, would do it but not sure how controller
    //is going to work
   /*
    toController(this->todisplay);
    if(this->todo)
    {
        frecover;
    }
    */    
}

