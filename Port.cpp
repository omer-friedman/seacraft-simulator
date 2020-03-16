//
// Created by omer on 21/06/18.
//

#include "Port.h"

Port::Port(string name, position location, double fuelCapacity,double fuelCreation):
        Simulator_object(move(name), location,PORT),fuel_capacity(fuelCapacity),fuel_creation(fuelCreation){
}

/*
 * printStatus:
 * Function will print the port status.
 * what position the port is and how may fuel it has.
 */
void Port::printStatus() {
    cout << "Port " << name <<" at position " <<"("<<location.first<<","<<location.second<<"), ";
    cout << "Fuel available: " << fuel_capacity <<" kl"<<endl;
}

/*
 * update:
 * Function will update the port for the next time.
 * will creat fuel and will fuel ships that waiting to be fueled.
 */
void Port::update() {
    create_fuel();
    DutyShip_wptr shipToFuel;
    double neededFuel,canFuel=0;
    while(!waiting_for_fuel.empty() && fuel_capacity!=0){
        shipToFuel=waiting_for_fuel.front();
        neededFuel = shipToFuel.lock()->getMaxFuel()-shipToFuel.lock()->getCurrentFuel();
        if(fuel_capacity>=neededFuel) {
            canFuel=neededFuel;
        }
        else if(fuel_capacity!=0) {
            canFuel=fuel_capacity;
        }
        shipToFuel.lock()->addFuel(canFuel);
        fuel_capacity-=canFuel;
        waiting_for_fuel.pop();
    }
}