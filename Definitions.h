//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_DEFINITIONS_H
#define SEASIMULATOR_DEFINITIONS_H

#include <string>
#include <utility>
#include <iostream>
#include <memory>

class Port;
class Ship;
class Duty_ship;
class Simulator_object;
class Track_base;
class Patrol_boat;
class Freighter;
class Cruiser;
using namespace std;

typedef double nautical_mile;
typedef enum{STOPPED,DOCKED,DEADINWATER,MOVINGTOPOSITION,MOVINGTOPORT,MOVINGONCOURSE} cruise_status;
typedef enum{FREIGHTER,PATROLBOAT,CRUISER,WRONGST} ship_type;
typedef enum{SHIP,PORT} object_type;
typedef enum{DEFAULT,SIZE,ZOOM,PAN,SHOW,STATUS,GO,CREATE,WRONGMV}modelViewCommand;
typedef enum{COURSE,POSITION,DESTINATION,LOAD_AT,UNLOAD_AT,DOCKAT,ATTACK,REFUEL,STOP,WRONGSC}shipCommand;
typedef enum{SUCCEED,NOTSUCCEED}success;
typedef pair<nautical_mile,nautical_mile> position;
typedef shared_ptr<Port> Port_sptr;
typedef shared_ptr<Ship> Ship_sptr;
typedef weak_ptr<Port> Port_wptr;
typedef weak_ptr<Ship> Ship_wptr;
typedef weak_ptr<Duty_ship> DutyShip_wptr;
typedef weak_ptr<Patrol_boat> Patrol_boat_wptr;
typedef weak_ptr<Freighter> Freighter_wptr;
typedef weak_ptr<Cruiser> Cruiser_wptr;
typedef weak_ptr<Simulator_object> Simulator_object_wptr;
typedef shared_ptr<Simulator_object> Simulator_object_sptr;
typedef shared_ptr<Track_base> Track_base_sptr;

#endif //SEASIMULATOR_DEFINITIONS_H
