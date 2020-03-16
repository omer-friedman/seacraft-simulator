//
// Created by omer on 21/06/18.
//

#include "Track_base.h"

void Track_base::setCruiseStatus(ship_type shipType, cruise_status cruiseStatus) {
    status= (shipType==CRUISER) ? MOVINGONCOURSE : cruiseStatus;
}
