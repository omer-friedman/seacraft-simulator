//
// Created by omer on 30/06/18.
//

#ifndef SEASIMULATOR_SHIPFACTORY_H
#define SEASIMULATOR_SHIPFACTORY_H

#include "Definitions.h"
#include "Cruiser.h"
#include "Patrol_boat.h"
#include "Freighter.h"


class ShipFactory {
public:
    ShipFactory() = default;
    Ship_sptr makeShip(ship_type st,string name,position ps, int arg1, int arg2=0){
        Ship_sptr ship;
        switch(st){
            case CRUISER:
                ship = make_shared<Cruiser>(name,ps,arg1,arg2);
                break;
            case PATROLBOAT:
                ship = make_shared<Patrol_boat>(name,ps,arg1);
                break;
            case FREIGHTER:
                ship = make_shared<Freighter>(name,ps,arg1,arg2);
                break;
            default:break;
        }
        return ship;
    }
};


#endif //SEASIMULATOR_SHIPFACTORY_H
