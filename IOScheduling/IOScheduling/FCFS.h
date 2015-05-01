//
//  FCFS.h
//  IOScheduling
//
//  Created by Haoran Jia on 4/29/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#ifndef __IOScheduling__FCFS__
#define __IOScheduling__FCFS__

#include <stdio.h>
#include "IOScheduler.h"

class FCFS : public IOScheduler
{
public:
    int nextRequest();
};

#endif /* defined(__IOScheduling__FCFS__) */
