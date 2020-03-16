//
// Created by omer on 21/06/18.
//

#include "Patrol_boat.h"

/*
 * printStatus:
 * Function will print the patrol-boat specific status.
 */
void Patrol_boat::printStatus() {
    Duty_ship::printStatus();
    switch(boatStatus){
        case FUELING:
            if(current_fuel==PATROL_MAX_FUEL)
                cout << ", fuel tank is full.";
            break;
        case SAILSOFFTHEBOAT:
            cout << ", sails get off the boat";
            break;
        case SETNEXTDESTINATION:
            cout << ", setting next destination.";
            break;
        case NOTINPORT:break;
        case DONETOUR:
            cout << ", done tour.";
            break;
    }
    cout << endl;
}

Patrol_boat::Patrol_boat(const string &name, position startPos, int resistance)
        : Duty_ship(name, startPos, PATROLBOAT, resistance, PATROL_MAX_FUEL), boatStatus(NOTINPORT){
}

/*
 * shipAttack:
 * Function will change some properties if the cruiser attack was succeed.
 */
void Patrol_boat::shipAttacked(success sec) {
    if(sec==SUCCEED) {
        if (resistance > 0)
            resistance--;
        stopShip();
    }
    else
        resistance++;
}

/*
 * update:
 * Function will update the patrol-boat to the next time according to the properties.
 */
void Patrol_boat::update() {
    if(trackBase->getCruiseStatus()==STOPPED)
        return;
    if(boatStatus==NOTINPORT)
        moveToNextLocation();
    if(trackBase->getCruiseStatus()==DOCKED){
        if(portTrack.empty())
        {
            boatStatus=DONETOUR;
            stopShip();
            return;
        }
        if(boatStatus==SETNEXTDESTINATION){
            setDutyShip(MOVINGTOPORT,portTrack.front(),lastSpeed);
            portTrack.pop();
            moveToNextLocation();
        }
        nextStatus();
    }
}

/*
 * stopShip:
 * Function will empty the portTrack and stop the ship.
 */
void Patrol_boat::stopShip() {
    while(!portTrack.empty()){portTrack.pop();}
    Duty_ship::stopShip();
}




