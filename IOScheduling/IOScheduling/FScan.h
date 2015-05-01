//
//  FScan.h
//  IOScheduling
//
//  Created by Haoran Jia on 4/30/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#ifndef __IOScheduling__FScan__
#define __IOScheduling__FScan__

#include <stdio.h>
#include "IOScheduler.h"

class FScan : public IOScheduler
{
public:
    deque<request> activeQueue, storeQueue;
    bool trace;
    FScan();
    
    void run(string inputFile, bool verbose);
    int nextUpFloor();
    int nextDownFloor();
    int nextRequest();
};

#endif /* defined(__IOScheduling__FScan__) */
