//
// Created by omer on 21/06/18.
//

#include "Cruiser.h"

/*
 * Cruiser:
 * Constructor, get name, position, force and distance, and set a the cruiser parameters.
 */
Cruiser::Cruiser(string name, position location, int force, int dis):
        Ship(move(name), location, CRUISER),attack_force(force),attack_distance(dis){
}

/*
 * tryAttackDutyShip:
 * Function will try to attack a duty ship (according to the ship resistance)
 * will update force and return succeed if attack was succeed, else return not succeed.
 * The model will take care of telling the duty ship if the attack was succeed or not.
 */
success Cruiser::tryAttackDutyShip(DutyShip_wptr ds) {
    if(attack_force > ds.lock()->getResistance()){
        attack_force++;
        return SUCCEED;
    }
    attack_force--;
    return NOTSUCCEED;
}

/*
 * printStatus:
 * print cruiser status.
 */
void Cruiser::printStatus() {
    Ship::printStatus();
    cout << setprecision(2) << fixed;
    cout << "force: "<<attack_force<<", ";
    cout << "Moving on course "<<trackBase->getCourse() <<" deg, ";
    cout << "speed "<< trackBase->getSpeed()<<" nm/hr" <<endl;
}

/*
 * update:
 * Function will update cruiser.
 */
void Cruiser::update() {
    moveToNextLocation();
}