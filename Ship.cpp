//
// Created by omer on 21/06/18.
//

#include "Ship.h"

Ship::Ship(string name, position pos, ship_type sType):
        Simulator_object(move(name), pos, SHIP),shipType(sType),
        trackBase(new Track_base(sType==CRUISER? MOVINGONCOURSE : STOPPED)){
}

/*
 * printStatus:
 * Function will print the ship status (only properties that all ships have).
 */
void Ship::printStatus() {
    cout << setprecision(2) << fixed;
    cout << shipTypeToString() <<" "<< name << " at (" << location.first << "," << location.second <<") ";
}

/*
 * shipTypeToString:
 * Function will pharse frome shipType to string and will return the right string.
 */
string Ship::shipTypeToString() {
    if(shipType==CRUISER)   return "Cruiser";
    if(shipType==FREIGHTER) return "Freighter";
    if(shipType==PATROLBOAT) return "Patrol-boat";
    return "";
}

/*
 * moveToNextLocation:
 * Function will take the ship to the next location if the speed is not zero.
 */
void Ship::moveToNextLocation() {
    double speed = trackBase->getSpeed();
    if(speed==0) {
        return;
    }
    double course;
    course = trackBase->getCourse();
    setLocationX(location.first + (speed*sin(course*M_PI/180)));
    setLocationY(location.second + (speed*cos(course*M_PI/180)));
}

/*
 * calculateCourse:
 * Function will calculate the ship course according to the destination coordinate.
 */
double Ship::calculateCourse(nautical_mile destX, nautical_mile destY) {
        nautical_mile x,y,x1,y1;
        double course;
        x1 = location.first;
        y1 = location.second;
        x = destX-x1;
        y = destY-y1;
        course = atan2(x,y);
        if (course < 0.)
            course = 2. * M_PI + course;
        course = course * 180 / M_PI;
        return course;
}
