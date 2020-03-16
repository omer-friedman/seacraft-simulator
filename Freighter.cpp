//
// Created by omer on 21/06/18.
//

#include "Freighter.h"

Freighter::Freighter(string name, position creationPos, int maxContainers, int resistance) :
        Duty_ship(name, creationPos, FREIGHTER, resistance, FREIGHTER_MAX_FUEL), max_containers(maxContainers),
        current_containers(0){
}

/*
 * printStatus:
 * Function will print the status that connected only to freighter.
 */
void Freighter::printStatus() {
    Duty_ship::printStatus();
    cout << ", Containers: " <<current_containers;
    if(trackBase->getCruiseStatus()!=DEADINWATER) {
        if (loadPort.lock() != weak_ptr<Port>().lock())
            cout << ", Moving to loading destination.";
        else if (unloadPort.lock() != weak_ptr<Port>().lock())
            cout << ", Moving to unloading destination.";
        else
            cout << ", No cargo destination.";
    }
    cout << endl;
}

/*
 * shipAttacked:
 * Function will change some properties if the cruiser attack was succeed.
 */
void Freighter::shipAttacked(success sec) {
    if(sec==SUCCEED) {
        current_containers = 0;
        stopShip();
    }
}

/*
 * update:
 * Function will update the freighter to the next time according to the properties.
 */
void Freighter::update() {
    moveToNextLocation();
    if(trackBase->getCruiseStatus()==DOCKED) {
        //check if need to load some containers in this port.
        if((loadPort.lock() != weak_ptr<Port>().lock()) && loadPort.lock()->getName()==destinationPort.lock()->getName()){
            int needContainers = checkLoadContainers();
            current_containers+=needContainers;
            loadPort = weak_ptr<Port>();
        }
        //check if need to unload some containers in this port.
        else if(unloadPort.lock() != weak_ptr<Port>().lock() && unloadPort.lock()->getName()==destinationPort.lock()->getName()){
            int unloadContainers = checkUnloadContainers();
            unloadPort = weak_ptr<Port>();
            if(unloadContainers!=-1 && current_containers>=unloadContainers)
                current_containers-=unloadContainers;
            else{
                current_containers=0;
                throw NotEnoughContainersException();
            }
        }
    }
}

/*
 * stopShip:
 * Function will restart properties and will stop the ship.
 */
void Freighter::stopShip() {
    loadPorts.clear();
    unloadPorts.clear();
    dockAtPort=weak_ptr<Port>();
    unloadPort=weak_ptr<Port>();
    loadPort=weak_ptr<Port>();
    Duty_ship::stopShip();
}

/*
 * insertNewCommand:
 * Function will insert a new command to the frieghter properties
 * to take care of in the next step.
 */
void Freighter::insertNewCommand(shipCommand sc, Port_wptr port, int cont=0) {
    if(sc==DOCKAT) {
        dockAtPort = port;
        return;
    }
    if(sc==LOAD_AT) {
        auto p = unloadPorts.find(port.lock()->getName());
        if(p!=unloadPorts.end())
            throw LoadAndUnloadException();
        loadPorts[port.lock()->getName()] = port;
    }
    else if(sc==UNLOAD_AT) {
        auto p = loadPorts.find(port.lock()->getName());
        if(p!=loadPorts.end())
            throw LoadAndUnloadException();
        unloadPorts[port.lock()->getName()] = {cont, port};
    }

    //this way, no matters if destination set first or load_at/unload_at set first.
    if(destinationPort.lock()!=shared_ptr<Port>())
        if(port.lock()->getName()==destinationPort.lock()->getName())
            sc == LOAD_AT? loadPort=port : unloadPort=port;
}

/*
 * checkUnloadContainers:
 * Function will check if there some containers to unload in the destination port, if there is
 * the function will return the amount of the containers, else return -1.
 */
int Freighter::checkUnloadContainers() {
    if(current_containers>0) {
        auto p = unloadPorts.find(destinationPort.lock()->getName());
        if (p != unloadPorts.end()) {
            unloadPorts.erase(p);
            return (*p).second.first;
        }
    }
    return -1;
}

/*
 * checkLoadContainers:
 * Function will check if there some containers to load in the destination port, if there is
 * the function will return the amount of the containers to load (depent on how much containers already have) , else return 0.
 */
int Freighter::checkLoadContainers() {
    int containersToLoad = max_containers - current_containers;
    if(containersToLoad>0) {
        auto p = loadPorts.find(destinationPort.lock()->getName());
        if (p != loadPorts.end()) {
            loadPorts.erase(p);
            return containersToLoad;
        }
    }
    return 0;
}
