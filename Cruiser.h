//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_CRUISER_H
#define SEASIMULATOR_CRUISER_H

#include <utility>
#include "Ship.h"
#include "Duty_ship.h"
#include "Exceptions.h"

#define CRUISER_MAX_SPEED 75

class Cruiser : public Ship{
public:
    ~Cruiser() override = default;
    Cruiser(string name,position location,int force, int dis);
    void update() override;
    void printStatus() override;
    success tryAttackDutyShip(DutyShip_wptr dsw);
    int getAttack_distance() const{return attack_distance;}
    double getMaxSpeed() override {return CRUISER_MAX_SPEED;}
    void setShipToAttack(DutyShip_wptr sta){shipToAttack= move(sta);}
    DutyShip_wptr getShipToAttack(){return shipToAttack;}

private:
    int attack_force;
    int attack_distance;
    DutyShip_wptr shipToAttack;
};


#endif //SEASIMULATOR_CRUISER_H
