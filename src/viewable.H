/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   viewable.H
 * Author: jeff
 *
 * Created on November 11, 2018, 6:10 PM
 */

#ifndef VIEWABLE_H
#define VIEWABLE_H

class viewable {
public:
    viewable();
    viewable(const viewable& orig);
    virtual ~viewable();
    virtual void toString() = 0;

private:

};

#endif /* VIEWABLE_H */

