//
// Created by omer on 21/06/18.
//

#include "View.h"

View::View(int sz, nautical_mile scl, double originX, double originY): size{sz},scale{scl},origin{originX,originY}{}

/*
 * show:
 * Function will print the board with all objects fit in the board
 * according to scale, origin and board size.
 */
void View::show() {
    int row,column,j;
    Simulator_object_sptr sim_obj;
    row = (int)scale*(int)NUMBEROFSCALESPACES;
    row *= (ceil(size/NUMBEROFSCALESPACES));
    row += (int)origin.second;
    cout<< setprecision(2) << fixed;
    cout << "Display size: "<<size;
    cout<<", scale: " <<scale;
    cout<<", origin: ("<<origin.first<<","<<origin.second<<")"<<endl;
    for(int i=size;i>0;i--)
    {
        cout << setw(3);
        if((i-1)%3==0)
            cout << row;
        else
            cout << " ";
        cout <<" ";
        column = (int)origin.second;
        for(j=size;j>0;j--){
            sim_obj = Model::getInstance().getObjectByLocationAndScale(column, row, scale);
            cout << ((sim_obj==nullptr)? ". " : sim_obj->getName().substr(0, 2));
            column+=scale;
        }
        row-=scale;
        cout<<endl;
    }
    column = (int)origin.first;
    for(int i=0;i<size;i++,column+=scale)
    {
        if(i%3==0)
            cout << setw(5) << (int)column << setw(1) <<" ";
    }
    cout << endl;
}

void View::setDefaultSettings() {
    size = DEFSIZE;
    scale = DEFSCALE;
    origin.first = ORIGINX;
    origin.second = ORIGINY;
}