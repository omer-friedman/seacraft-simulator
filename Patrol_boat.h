//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_PATROL_BOAT_H
#define SEASIMULATOR_PATROL_BOAT_H


#include "Duty_ship.h"
#include <queue>
#include <utility>
#include "Exceptions.h"

#define PATROL_MAX_FUEL 900000
#define PATROL_MAX_SPEED 15
#define PATROL_FUEL_CONSUMPTION 2000

//boat status when docked in a port.
typedef enum{FUELING,SAILSOFFTHEBOAT,SETNEXTDESTINATION,NOTINPORT,DONETOUR} boat_position;

class Patrol_boat : public Duty_ship{
public:
    ~Patrol_boat() override = default;
    Patrol_boat(const string &name, position startPos, int resistance);
    void update() override; //update ship to next time
    void printStatus() override; //print specific patrol-boat status.
    void shipAttacked(success sec) override;
    double getMaxSpeed() override {return PATROL_MAX_SPEED;}
    double getFuelConsumption() override {return PATROL_FUEL_CONSUMPTION;}
    double getMaxFuel() override {return PATROL_MAX_FUEL;}
    void nextStatus(){boatStatus = (boat_position)((boatStatus+1)%4);} //set next boat status
    void setNextStatus(boat_position bp){boatStatus=bp;}
    void setPortTrack(queue<Port_wptr> prtTrack){portTrack= move(prtTrack);}
    boat_position getBoatStatus(){return boatStatus;}
    void stopShip() override; //to stop the ship.

private:
    queue<Port_wptr> portTrack; //ports need to visit
    boat_position boatStatus;
};
#endif //SEASIMULATOR_PATROL_BOAT_H
