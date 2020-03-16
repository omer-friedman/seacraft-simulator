//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_MODEL_H
#define SEASIMULATOR_MODEL_H

#include <sstream>
#include <fstream>
#include <list>
#include <algorithm>
#include "Port.h"
#include "ShipFactory.h"
#include "Exceptions.h"
#include "HelpFunctions.h"

class Model {
public:
    Model(const Model&) = delete;
    Model(const Model&&) = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(const Model&&) = delete;
    static Model& getInstance();
    Simulator_object_sptr getObjectByLocationAndScale(nautical_mile col, nautical_mile row, nautical_mile scale);
    void setShipCourse(Ship_wptr ship, double course, double speed);
    void setShipPosition(Ship_wptr ship, nautical_mile shipX, nautical_mile shipY, double speed);
    void setShipPort(Ship_wptr ship,Port_wptr destPort, double speed, cruise_status cs=MOVINGTOPORT);
    void setShipCommand(Ship_wptr ship, shipCommand sc, Simulator_object_sptr obj= nullptr, int cont=0);
    void createShip(stringstream& ss);
    void printAllObjectsStatus();
    void readInput(string file);
    const int getTime(){return simTime;}
    void updateAll();
    Ship_sptr getShipByName(string name);
    Port_sptr getPortByName(string portName);

private:
    list<Ship_sptr> ships;
    list<Port_sptr> ports;
    ShipFactory ship_factory;
    int simTime;
    Model();
    ~Model() = default;
    bool isInputLineOk(string &name,double &x, double &y, double &arg1, double &arg2, stringstream &ss);
    bool checkInScale(position pos,nautical_mile col, nautical_mile row, nautical_mile scale);
    void cruiserAttack(Cruiser_wptr cruiser, DutyShip_wptr shipToAttack);
    void fillPatrolboatTrack(Port_wptr, list<Port_sptr> leftPorts, queue<Port_wptr> &portTrack);
    double getDistance(position locA, position locB);
};


#endif //SEASIMULATOR_MODEL_H
