//
//  Elevator.h
//  IOScheduling
//
//  Created by Haoran Jia on 4/30/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#ifndef __IOScheduling__Elevator__
#define __IOScheduling__Elevator__

#include <stdio.h>
#include "IOScheduler.h"

class Elevator : public IOScheduler
{
public:
    int nextRequest();
    int nextUpFloor();
    int nextDownFloor();
};

#endif /* defined(__IOScheduling__Elevator__) */
