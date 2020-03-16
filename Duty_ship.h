//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_DUTY_SHIP_H
#define SEASIMULATOR_DUTY_SHIP_H

#include "Definitions.h"
#include "Ship.h"
#include "Port.h"

class Duty_ship : public Ship{
public:
    Duty_ship(string name, position loc, ship_type st, int resistance, double maxFuel);
    ~Duty_ship() override = default;
    virtual double getFuelConsumption()=0; //
    virtual double getMaxFuel()=0;         //  get those information from a specific ship (freighter or patrol)
    double getMaxSpeed() override =0;      //
    virtual void shipAttacked(success sec)=0;
    virtual void stopShip()=0;
    void update() override =0;
    bool consumeFuel(); //consume fuel according to "getFuelConstumption" function.
    void printStatus() override; //print duty ship status (properties that also freighter and patrol-boat have)
    void addFuel(double nwFuel);
    double getCurrentFuel(){return current_fuel;}
    const int getResistance() const {return resistance;}
    void setDestinationCoor(nautical_mile x, nautical_mile y){destinationCoordinate={x,y};}
    void moveToNextLocation() override; //make a single move to the next location.
    void setNeedRefuel(bool need){needRefuel = need;}
    bool isNeedToRefuel(){return needRefuel;}
    Port_wptr getDestinationPort(){return destinationPort;}
    void setDutyShip(cruise_status cs,Port_wptr port, double speed=0); //set duty ship port
    void setDutyShip(cruise_status cs, nautical_mile x, nautical_mile y, double speed); //set duty ship position

protected:
    position destinationCoordinate;
    Port_wptr destinationPort;
    int resistance;
    double current_fuel;
    bool needRefuel;
    double lastSpeed;
};


#endif //SEASIMULATOR_DUTY_SHIP_H
