/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   selectable.H
 * Author: jeff
 *
 * Created on November 12, 2018, 4:45 PM
 */

#ifndef SELECTABLE_H
#define SELECTABLE_H

using namespace std;

class selectable {
public:
    selectable();
    selectable(const selectable& orig);
    virtual ~selectable();
    
    virtual void selected() = 0;
private:

};

#endif /* SELECTABLE_H */

