//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_VIEW_H
#define SEASIMULATOR_VIEW_H


#include "Definitions.h"
#include <iomanip>
#include "Model.h"

#define NUMBEROFSCALESPACES 3
#define DEFSIZE 25
#define DEFSCALE 2
#define ORIGINX 0
#define ORIGINY 0

class View {
public:
    explicit View(int sz=DEFSIZE, nautical_mile scl=DEFSCALE, double originX=ORIGINX,double originY=ORIGINY);
    ~View() = default;
    void show(); //print board to the standart output.
    //setters
    void setDefaultSettings();
    void setSize(int sz){size=sz;}
    void setScale(nautical_mile scl){scale=scl;}
    void setOriginX(nautical_mile loc){origin.first=loc;}
    void setOriginY(nautical_mile loc){origin.second=loc;}

private:
    int size;
    nautical_mile scale;
    position origin;
};


#endif //SEASIMULATOR_VIEW_H
