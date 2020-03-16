//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_SIMULATOR_OBJECT_H
#define SEASIMULATOR_SIMULATOR_OBJECT_H

#include "Definitions.h"

class Simulator_object {
public:
    virtual ~Simulator_object() = default;
    Simulator_object(string objName, position objLocation,object_type ot):
            name(move(objName)),location(move(objLocation)),objectType(ot){};
    const position getLocation() const {return location;}
    const string getName() const {return name;}
    void setLocationX(nautical_mile x){location.first = x;}
    void setLocationY(nautical_mile y){location.second = y;}
    virtual void update()=0;
    virtual void printStatus()=0;

protected:
    string name;
    position location;
    object_type objectType;
};


#endif //SEASIMULATOR_SIMULATOR_OBJECT_H
