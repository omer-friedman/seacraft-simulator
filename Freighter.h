//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_FREIGHTER_H
#define SEASIMULATOR_FREIGHTER_H

#include <utility>
#include "Definitions.h"
#include "Duty_ship.h"
#include "Exceptions.h"

#define FREIGHTER_MAX_FUEL 500000
#define FREIGHTER_MAX_SPEED 40
#define FREIGHTER_FUEL_CONSUMPTION 1000

class Freighter : public Duty_ship{
public:
    ~Freighter() override = default;
    Freighter(string name, position creationPos, int max_containers, int resistance);
    void update() override; //update freighter
    void printStatus() override; //print specific freighter status
    void shipAttacked(success sec) override;
    double getMaxSpeed() override {return FREIGHTER_MAX_SPEED;}
    double getFuelConsumption() override {return FREIGHTER_FUEL_CONSUMPTION;}
    double getMaxFuel() override {return FREIGHTER_MAX_FUEL;}
    void stopShip() override;
    void insertNewCommand(shipCommand sc, Port_wptr port, int cont); //insert command according to shipCommand.
    map<string,Port_wptr> getLoadPorts(){return loadPorts;}
    map<string,pair<int,Port_wptr>> getUnloadPorts(){return unloadPorts;}
    void setLoadPort(Port_wptr port){loadPort = move(port);}
    void setUnloadPort(Port_wptr port){unloadPort = move(port);}
    int checkUnloadContainers(); //check for unload containers
    int checkLoadContainers();  //check how many containars can load in the loadPort
    Port_wptr getDockAtPort(){return dockAtPort;}
    void resetDockAt(){dockAtPort=weak_ptr<Port>();}

private:
    int max_containers;
    int current_containers;
    Port_wptr loadPort;
    Port_wptr unloadPort;
    Port_wptr dockAtPort;
    map<string,Port_wptr> loadPorts;
    map<string,pair<int,Port_wptr>> unloadPorts;
};


#endif //SEASIMULATOR_FREIGHTER_H
