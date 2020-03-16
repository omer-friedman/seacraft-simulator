//
// Created by omer on 21/06/18.
//

#include "Model.h"

Model& Model::getInstance() {
    static Model inst;
    return inst;
}

/**
 * getObjectByLocationAndScale:
 * Function will get column number, row number and scale and return the object that feet
 * in this scale. function will prefer to return a port than a ship if both feet.
 */
Simulator_object_sptr Model::getObjectByLocationAndScale(nautical_mile col, nautical_mile row, nautical_mile scale) {
    scale = scale/2;
    for(auto so : ports)
        if(checkInScale(so->getLocation(),col,row,scale))
            return so;
    for(auto so : ships)
        if(checkInScale(so->getLocation(),col,row,scale)) {
            return so;
        }
    return nullptr;
}

/*
 * checkInScale:
 * help function to tell if this position is between column and row with scale.
 */
bool Model::checkInScale(position pos, nautical_mile col, nautical_mile row, nautical_mile scale) {
    nautical_mile objX,objY;
    objX=pos.first;
    objY=pos.second;
    if(objX<=col+scale && objX > col-scale)
        if(objY<=row+scale && objY > row-scale)
            return true;
    return false;
}

/*
 * Model:
 * Constructor- set time to be zero and initialize a new port
 */
Model::Model():simTime{0} {
    Port_sptr nwPort(new Port("Nagoya",{50,5},1000000,1000));
    ports.push_front(nwPort);
}

/*
 * getShipByName:
 * Function gets a ship name and return the ship object if exist.
 * if not exist the function will return an empty shared_ptr
 */
Ship_sptr Model::getShipByName(string name) {
    for(const auto &ship : ships) {
        if (ship->getName() == name)
            return ship;
    }
    return shared_ptr<Ship>();
}

/*
 * getPortByName:
 * Function gets a port name and return the port object if exist.
 * if not exist the function will return an empty shared_ptr
 */
Port_sptr Model::getPortByName(string portName) {
    for(const auto &port : ports)
        if(port->getName() == portName)
            return port;
    return shared_ptr<Port>();
}

/*
 * printAllObjectsStatus:
 * Function will print to the standrat output all objects status.
 */
void Model::printAllObjectsStatus() {
    for(const auto &port: ports) {
        port->printStatus();
    }
    for(const auto &ship: ships) {
        ship->printStatus();
    }
}

/*
 * readInput:
 * Function will read all ports from file (if exist) and will add the ports to the port list.
 */
void Model::readInput(string fileName) {
    fstream ifs(fileName.c_str(),ios::in);
    if(!ifs.is_open())
        throw OpenFileException();

    string line,name;
    double portX, portY, fuelCapacity, fuelCreation;

    while(getline(ifs,line)) //there is still lines to read.
    {
        stringstream ss(line);
        if(!isInputLineOk(name, portX, portY, fuelCapacity, fuelCreation, ss)) //check if input is ok
            throw WrongInputException();
        Port_sptr nwPort(new Port(name,{portX,portY},fuelCapacity,fuelCreation));
        ports.push_back(nwPort);
    }
}

/*
 * isInputLineOk:
 * Function will pharse the input from the user and return true if the input ok, else it will return false.
 */
bool Model::isInputLineOk(string &name,double &x, double &y, double &arg1, double &arg2, stringstream &ss) {
	
    char c1,c2,c3;
    ss>>name>>c1>>x>>c2>>y>>c3>>arg1>>arg2;
	if(name.length()>12 || arg1<0 || arg2<0 || c1!='(' || c2!=',' || c3!=')')
		return false;

	for(char c : name)  //check if name is only alphabet
		if(!isalpha(c))
			return false;

    return true;
}

/*
 * cruiserAttack:
 * Function will try to attack the duty ship given.
 * the act will seccess if the cruiser attack force is larger than the duty ship resistance
 * and if the distance attack not smaller than the distance of the ship.
 */
void Model::cruiserAttack(Cruiser_wptr cruiser, DutyShip_wptr shipToAttack) {
    nautical_mile attack_distacne = cruiser.lock()->getAttack_distance();
    double dist = getDistance(cruiser.lock()->getLocation(), shipToAttack.lock()->getLocation());

    if (dist <= attack_distacne) { //check if distance attack is larger
        if (cruiser.lock()->tryAttackDutyShip(shipToAttack) == SUCCEED) //check attack force agains resistance.
            shipToAttack.lock()->shipAttacked(SUCCEED); //tell the ship that attack succeed.
        else
            shipToAttack.lock()->shipAttacked(NOTSUCCEED);
        cruiser.lock()->setShipToAttack(weak_ptr<Duty_ship>()); //reset the ship to attack.
    } else{
        cruiser.lock()->setShipToAttack(weak_ptr<Duty_ship>());
        throw AttackTooFarException();
    }
}
/*
 * updateAll:
 * Function will update all objects in the game
 * and will update himself a few thigs of the objects.
 */
void Model::updateAll() {
    simTime++;
    for(const auto &ship : ships) {
        ship_type st = ship->getShipType();
        if (st == CRUISER) { //check if cruiser has a ship to attack.
            Cruiser_wptr cr = dynamic_pointer_cast<Cruiser>(ship);
            DutyShip_wptr tmpDShip = cr.lock()->getShipToAttack();
            if (tmpDShip.lock() != weak_ptr<Duty_ship>().lock()) {
                try {
                    cruiserAttack(cr, tmpDShip);
                }catch(exception& e){cout << e.what() << endl;}
            }
            ship->update();
            continue;
        }
        DutyShip_wptr ds = dynamic_pointer_cast<Duty_ship>(ship);
        if (st == FREIGHTER) {//check if freighter wants to dock at a port
            Freighter_wptr fr = dynamic_pointer_cast<Freighter>(ds.lock());
            Port_wptr tmpPort = fr.lock()->getDockAtPort();
            if (tmpPort.lock() != weak_ptr<Port>().lock()) {
                fr.lock()->resetDockAt();
                double dist = getDistance(fr.lock()->getLocation(), tmpPort.lock()->getLocation());
                if (dist <= 0.1)
                    setShipPort(fr, tmpPort, DOCKED);
                else
                    throw DockAtPortException();
            }
        }
        ship->update();
        /* fuel duty ship */
        if (ds.lock()->isNeedToRefuel() && ds.lock()->getTrackBase()->getCruiseStatus() == DOCKED) {
            if (st == PATROLBOAT) {
                Patrol_boat_wptr pb = dynamic_pointer_cast<Patrol_boat>(ds.lock());
                if (pb.lock()->getBoatStatus() != FUELING)
                    continue;
            }
            ds.lock()->getDestinationPort().lock()->addToWaitingFuelList(ds);
        }
    }

    for(const auto &port : ports){
        port->update();
    }
}

/*
 * setShipCourse:
 * Function will set ship status, course and speed.
 */
void Model::setShipCourse(Ship_wptr ship, double course, double speed) {
    ship.lock()->setCruiseStatus(MOVINGONCOURSE);
    ship.lock()->setCourse(course);
    ship.lock()->setSpeed(speed);
}

/*
 * setShipPosition:
 * Function will set ship sataus, position and speed
 */
void Model::setShipPosition(Ship_wptr ship, nautical_mile shipX, nautical_mile shipY, double speed) {
    dynamic_pointer_cast<Duty_ship>(ship.lock())->setDutyShip(MOVINGTOPOSITION, shipX, shipY, speed);
}

void Model::setShipPort(Ship_wptr ship, Port_wptr destPort, double speed, cruise_status cs) {
    DutyShip_wptr ds = dynamic_pointer_cast<Duty_ship>(ship.lock());
    ds.lock()->setDutyShip(cs,destPort,speed);

    //set patrol boat track road.
    if(ship.lock()->getShipType()==PATROLBOAT){
        Patrol_boat_wptr pbw = dynamic_pointer_cast<Patrol_boat>(ds.lock());
        pbw.lock()->setNextStatus(NOTINPORT);
        queue<Port_wptr> tmpPortTrack;
        list<Port_sptr> tmpList = ports;
        tmpList.remove_if([destPort](Port_wptr p){return !(p.owner_before(destPort) || destPort.owner_before(p));});
        fillPatrolboatTrack(destPort, tmpList, tmpPortTrack);
        tmpPortTrack.push(destPort);
        pbw.lock()->setPortTrack(tmpPortTrack);
        return;
    }
    //check if freighter need to load at this destination port
    if(ship.lock()->getShipType()==FREIGHTER){
       Freighter_wptr fw = dynamic_pointer_cast<Freighter>(ds.lock());
        map<string,Port_wptr> tmpLoadMap = fw.lock()->getLoadPorts();
        auto loadIt = tmpLoadMap.find(destPort.lock()->getName());
        if(loadIt!=tmpLoadMap.end()) {
            fw.lock()->setLoadPort(destPort);
            return;
        }
       map<string,pair<int,Port_wptr>> tmpUnloadMap = fw.lock()->getUnloadPorts();
       auto unloadIt = tmpUnloadMap.find(destPort.lock()->getName());
       if(unloadIt!=tmpUnloadMap.end())
           fw.lock()->setUnloadPort(destPort);
    }
}

/*
 * fillPatrolboatTrack:
 * Recursive function to fill patrol boat track when a port destination is set.
 */
void Model::fillPatrolboatTrack(Port_wptr lastPort, list<Port_sptr> leftPorts, queue<Port_wptr> &portTrack) {
    if(leftPorts.empty())
        return;
    //sort the rest of the ports by distance from the last port.
    leftPorts.sort([&](Port_wptr a, Port_wptr b) {
        position tmpPosA = a.lock()->getLocation();
        position tmpPosB = b.lock()->getLocation();
        position lastPortPos = lastPort.lock()->getLocation();
        double distanceA = getDistance(lastPortPos, tmpPosA);
        double distanceB = getDistance(lastPortPos, tmpPosB);
        if(distanceA == distanceB) //if both ports has the same distance, choose by alphabet order.
            return a.lock()->getName().compare(b.lock()->getName()) > 0;
        return  distanceA > distanceB;
    });
    Port_wptr nextPort = leftPorts.back();
    //check if two ports has the same location.
    if(nextPort.lock()->getLocation() != portTrack.front().lock()->getLocation()) {
        portTrack.push(nextPort);
    }
    leftPorts.pop_back();
    fillPatrolboatTrack(nextPort,leftPorts,portTrack);
}

/*
 * getDistance:
 * Function return the distance between point a to point b
 */
double Model::getDistance(position locA, position locB) {
    nautical_mile x1,x2,y1,y2,x,y;
    x1 = locA.first;
    x2 = locB.first;
    y1 = locA.second;
    y2 = locB.second;
    x = x2-x1;
    y = y2-y1;
    return sqrt((x*x)+(y*y));
}

/*
 * setShipCommand
 * Function set the ship command acording to the client input.
 */
void Model::setShipCommand(Ship_wptr ship, shipCommand sc, Simulator_object_sptr obj, int cont) {
    DutyShip_wptr ds;
    Freighter_wptr freighter;
    Cruiser_wptr cruiser;
    switch(sc){
        case DOCKAT:
        case LOAD_AT:
        case UNLOAD_AT:
            freighter = dynamic_pointer_cast<Freighter>(ship.lock());
            freighter.lock()->insertNewCommand(sc, dynamic_pointer_cast<Port>(obj), cont);
            break;
        case REFUEL:
            ds = dynamic_pointer_cast<Duty_ship>(ship.lock());
            ds.lock()->setNeedRefuel(true);
            break;
        case STOP:
            ds = dynamic_pointer_cast<Duty_ship>(ship.lock());
            ds.lock()->stopShip();
            break;
        case ATTACK:
            cruiser = dynamic_pointer_cast<Cruiser>(ship.lock());
            cruiser.lock()->setShipToAttack(dynamic_pointer_cast<Duty_ship>(obj));
            break;
        default:break;
    }
}

/*
 * createShip:
 * Function creating some ship, acording to client input, with help of a ship factory.
 * the function will add the ship to the list, if the input was ok.
 */
void Model::createShip(stringstream &ss) {
    stringstream tmpSS;
    nautical_mile x,y;
    string shipName,shipType,restStr;
    double res,optCom;
    ss >> shipName >> shipType;
    getline(ss,restStr);
    tmpSS <<shipName<<" "<<restStr;
    ship_type st = string_to_ShipType(shipType);
    if(!isInputLineOk(shipName,x,y,res,optCom,tmpSS) || st==WRONGST)
        throw WrongShipDetailsException();
    if(getShipByName(shipName) != shared_ptr<Ship>())
        throw ShipAlreadyExistException();
    /* insert to the list sorted by ship type, cruiser will insert in the back of the list.
     * this way cruisers will update last and can attack ships if the other ship is close enough*/
    Ship_sptr nwShip = ship_factory.makeShip(st,shipName,{x,y},(int)res,(int)optCom);
    ships.insert(lower_bound(ships.begin(),ships.end(),nwShip,[](Ship_sptr s1,Ship_sptr s2){return s1->getShipType()<s2->getShipType();}),nwShip);
}