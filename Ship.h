//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_SHIP_H
#define SEASIMULATOR_SHIP_H

#include "Simulator_object.h"
#include "Track_base.h"
#include <iomanip>
#include <cmath>
#include <map>

class Ship : public Simulator_object {
public:
    ~Ship() override = default;
    Ship(string name, position pos ,ship_type sType);
    void update() override =0;
    void printStatus() override;
    string shipTypeToString(); //pharse ship type to string
    virtual void moveToNextLocation(); //make a single move to the next location
    const ship_type getShipType() const{return shipType;}
    bool isDeadShip(){return trackBase->getCruiseStatus()==DEADINWATER;} //check if ship is dead in water.
    virtual double getMaxSpeed() = 0;
    double calculateCourse(nautical_mile destX, nautical_mile destY); //calculate course according to coordinate.
    void setCruiseStatus(cruise_status cs){trackBase->setCruiseStatus(shipType,cs);}
    void setCourse(double course){trackBase->setCourse(course);}
    void setSpeed(double speed){trackBase->setSpeed(speed);}
    Track_base_sptr getTrackBase(){return trackBase;}
protected:
    ship_type shipType;
    Track_base_sptr trackBase;
};



#endif //SEASIMULATOR_SHIP_H
