//
//  FCFS.cpp
//  IOScheduling
//
//  Created by Haoran Jia on 4/29/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#include "FCFS.h"

int FCFS::nextRequest()
{
    int ret = 0;
    for (deque<request>::iterator it = ioqueue.begin(); it != ioqueue.end(); it++) {
        if (!it->finished) {
            ret = (int)(it - ioqueue.begin());
            break;
        }
    }
    return ret;
}