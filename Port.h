//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_PORT_H
#define SEASIMULATOR_PORT_H


#include "Simulator_object.h"
#include "Duty_ship.h"
#include <queue>

class Port : public Simulator_object{
public:
    ~Port() override = default;
    Port(string name,position location,double fuelCapacity, double fuelCreation);
    void create_fuel(){fuel_capacity+=fuel_creation;} //create fuel according to fuel creation
    void addToWaitingFuelList(DutyShip_wptr ship) {waiting_for_fuel.push(ship);} //add ship to waiting for fuel list
    void update() override; //update port for next time
    void printStatus() override; //print specific port status

private:
    double fuel_capacity;
    double fuel_creation;
    queue<DutyShip_wptr> waiting_for_fuel;
};

#endif //SEASIMULATOR_PORT_H
