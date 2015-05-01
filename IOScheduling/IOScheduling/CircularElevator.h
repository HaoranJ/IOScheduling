//
//  CircularElevator.h
//  IOScheduling
//
//  Created by Haoran Jia on 4/30/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#ifndef __IOScheduling__CircularElevator__
#define __IOScheduling__CircularElevator__

#include <stdio.h>
#include "IOScheduler.h"

class CircularElevator : public IOScheduler
{
public:
    int nextRequest();
    int nextUpFloor();
};

#endif /* defined(__IOScheduling__CircularElevator__) */
