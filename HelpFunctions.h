//
// Created by omer on 21/06/18.
//

#ifndef SEASIMULATOR_HELPFUNCTIONS_H
#define SEASIMULATOR_HELPFUNCTIONS_H


#include "Definitions.h"
#include <algorithm>

modelViewCommand string_to_MV_command(string str);
shipCommand string_to_shipCommand(string str);
ship_type string_to_ShipType(string str);
void strToLower(string& str);
bool checkBoardSize(int sz);

#endif //SEASIMULATOR_HELPFUNCTIONS_H
