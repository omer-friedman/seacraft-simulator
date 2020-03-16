//
// Created by omer on 21/06/18.
//

#include "Duty_ship.h"

/*
 * Duty_ship Constructor
 */
Duty_ship::Duty_ship(string name, position loc, ship_type st, int res, double maxFuel) :
        Ship(move(name),loc,st),resistance(res),current_fuel(maxFuel){}

/*
* printStatus:
 * Function will print status of the duty ship
 * (properties that the same for also freighter and patrol-boat)
*/
void Duty_ship::printStatus() {
    Ship::printStatus();
    cout << setprecision(2) << fixed;
    cout << "fuel: "<<current_fuel<<" kl, ";
    cout << "resistance: " << resistance<<", ";
    switch(trackBase->getCruiseStatus())
    {
        case(STOPPED):
            cout << "Ship stopped";
            break;
        case(DOCKED):
            cout << "Docking in " << destinationPort.lock()->getName();
            break;
        case(DEADINWATER):
            cout << "Dead in water";
            break;
        case(MOVINGTOPOSITION):
            cout << "Moving to position" << "("<<destinationCoordinate.first<<","<<destinationCoordinate.second<<")";
            cout << " on course " << trackBase->getCourse();
            break;
        case(MOVINGTOPORT):
            cout << "Moving to " << destinationPort.lock()->getName();
            cout << " on course " << trackBase->getCourse();
            break;
        case(MOVINGONCOURSE):
            cout << "Moving on course" << trackBase->getCourse();
            break;
    }
}

/*
 * consumeFuel:
 * Function will consume fuel according to how much fuel this ship is consuming per 1 time.
 * the function will return true if there is a fuel to consume,
 * else will return false (and the ship will stack without fuel in the middle of the sea)
 */
bool Duty_ship::consumeFuel() {
    double fuelConsumption = getFuelConsumption();
    if(current_fuel-fuelConsumption >= 0 ){
        current_fuel-=fuelConsumption;
        return true;
    }
    current_fuel=0;
    return false;
}

/*
 * moveToNextLocation:
 * Function will set the cruiser properties for the next move
 * and will take the ship to the next location according to those properties.
 */
void Duty_ship::moveToNextLocation() {
    cruise_status cs = trackBase->getCruiseStatus();
    if(cs==MOVINGTOPORT || cs == MOVINGTOPOSITION){
        position coor = (cs==MOVINGTOPORT? destinationPort.lock()->getLocation() : destinationCoordinate);
        nautical_mile x = coor.first - location.first;
        nautical_mile y = coor.second - location.second;
        double distance = sqrt((x*x)+(y*y));
        double speed = trackBase->getSpeed();
        if(speed>0) {
            if(distance>0 && !consumeFuel()) { //if ship has enough fuel to get to the next location
                trackBase->setCruiseStatus(shipType, DEADINWATER);
                trackBase->setSpeed(0);
                return;
            }
            if (distance <= speed || (shipType==FREIGHTER && distance-speed<=0.1)) {
                setLocationX(coor.first);
                setLocationY(coor.second);
                cs==MOVINGTOPORT? trackBase->setCruiseStatus(shipType,DOCKED) : trackBase->setCruiseStatus(shipType, STOPPED);
                lastSpeed=trackBase->getSpeed();
                trackBase->setSpeed(0);
                return;
            }
        }
        else return;
    }
    Ship::moveToNextLocation();
}

/*
 * addFuel:
 * Function will add fuel the the currant fuel.
 */
void Duty_ship::addFuel(double nwFuel) {
    current_fuel+=nwFuel;
    if(current_fuel==getMaxFuel())
        needRefuel = false;
}

/*
 * setDutyShip:
 * Function will set duty ship port
 */
void Duty_ship::setDutyShip(cruise_status cs, Port_wptr port, double speed) {
    destinationPort=port;
    setCruiseStatus(cs);
    setSpeed(speed);
    if(cs!=DOCKED)
        setCourse(calculateCourse(port.lock()->getLocation().first,port.lock()->getLocation().second));
}

/*
 * Function will set duty ship position
 */
void Duty_ship::setDutyShip(cruise_status cs, nautical_mile x, nautical_mile y, double speed) {
    setCruiseStatus(cs);
    setSpeed(speed);
    setDestinationCoor(x,y);
    setCourse(calculateCourse(x,y));
}

/*
 * stopShip:
 * function will stop the ship by changing status to STOPPED and by setting speed to be 0.
 */
void Duty_ship::stopShip() {
    setCruiseStatus(STOPPED);
    setSpeed(0);
}


