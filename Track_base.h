//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_TRACK_BASE_H
#define SEASIMULATOR_TRACK_BASE_H

#include "Definitions.h"
#include "Exceptions.h"

/*
 * Track_base:
 * class to represent a moving ship properties.
 */
class Track_base {
public:
    ~Track_base() = default;
    explicit Track_base(cruise_status cs=STOPPED):course(0),speed(0),status(cs){};
    Track_base(const Track_base& rhs):course(rhs.course),speed(rhs.speed),status(rhs.status){*this = rhs;}
    //getters and setters:
    double getCourse() const {return course;}
    double getSpeed() const {return speed;}
    cruise_status getCruiseStatus(){return status;}
    void setCruiseStatus(ship_type shipType, cruise_status cruiseStatus);
    void setCourse(double crs){this->course = crs;}
    void setSpeed(double speed) {this->speed = speed;}
private:
    double course; //course that the ship move at
    double speed; //speed that the ship move at
    cruise_status status; //cruise status.
};


#endif //SEASIMULATOR_TRACK_BASE_H
