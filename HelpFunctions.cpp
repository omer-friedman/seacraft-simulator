//
// Created by omer on 21/06/18.
//

#include "HelpFunctions.h"

modelViewCommand string_to_MV_command(string str) {
    strToLower(str);
    if(str=="default") return DEFAULT;
    if(str=="size") return SIZE;
    if(str=="zoom") return ZOOM;
    if(str=="pan") return PAN;
    if(str=="show") return SHOW;
    if(str=="status") return STATUS;
    if(str=="go") return GO;
    if(str=="create") return CREATE;
    return WRONGMV;
}

shipCommand string_to_shipCommand(string str){
    strToLower(str);
    if(str=="course") return COURSE;
    if(str=="position") return POSITION;
    if(str=="destination") return DESTINATION;
    if(str=="load_at") return LOAD_AT;
    if(str=="unload_at") return UNLOAD_AT;
    if(str=="dock_at") return DOCKAT;
    if(str=="attack") return ATTACK;
    if(str=="refuel") return REFUEL;
    if(str=="stop") return STOP;
    return WRONGSC;
}
ship_type string_to_ShipType(string str){
    strToLower(str);
    if(str=="cruiser") return CRUISER;
    if(str=="freighter") return FREIGHTER;
    if(str=="patrol_boat") return PATROLBOAT;
    return WRONGST;
}

bool checkBoardSize(int sz) {
    if(sz<=30&&sz>6)
        return true;
    return false;
}

void strToLower(string &str) {transform(str.begin(), str.end(), str.begin(), ::tolower);}

//unsigned stoii(string & s)
//{
//	int size=s.length();
//	char c;
//	for(int i=0;i<size-1;i++) //check char by char if is a digit
//	{
//		c = s[i];
//		if(!isdigit(c))// if its not digit its not number
//			return -1;
//	}
//	return atoi(s.c_str());
//}


//bool getOriginFromString(string loc, nautical_mile& x, nautical_mile& y) {
//	//(x,y)
//	double orgX,orgY;
//	string str = loc.substr(loc.find('('), loc.find(','));
//	orgX = stoii(str);
//}
