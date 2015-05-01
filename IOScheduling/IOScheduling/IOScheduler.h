//
//  IOScheduler.h
//  IOScheduling
//
//  Created by Haoran Jia on 4/28/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#ifndef __IOScheduling__IOScheduler__
#define __IOScheduling__IOScheduler__

#include <stdio.h>
#include <deque>
#include <fstream>
#include <list>
#include <sstream>

#include "Request.h"

using namespace::std;

class IOScheduler
{
public:
    int head;
    int time;
    int totalRequest;
    int numio;
    int topTrack;
    int buttomTrack;
    bool upward;
    
    int totalTime;
    int totalMove;
    int totalTurnAround;
    int totalWait;
    int maxWait;
    int finishCount;
    
    deque<request> ioqueue;
    
    IOScheduler();
    
    void initRequest(string inputFile);
    
    void run(string inputFile, bool verbose);
    
    void displayResults();
    
    virtual int nextRequest() = 0;
    
    
};

#endif /* defined(__IOScheduling__IOScheduler__) */
