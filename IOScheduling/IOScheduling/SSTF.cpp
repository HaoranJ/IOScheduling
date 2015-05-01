//
//  SSTF.cpp
//  IOScheduling
//
//  Created by Haoran Jia on 4/29/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
// Shortest Seek Time First

#include "SSTF.h"
#include <climits>
#include <cstdlib>

int SSTF::nextRequest()
{
    int ret = -1;
    int dis = INT_MAX;
    deque<request>::iterator it = ioqueue.begin();
    while(it->added) {
        if (!it->finished) {
            int temp = abs(head - it->track);
            //printf("%d: seek time = %d\n", (int)(it - ioqueue.begin()), temp);
            if (temp < dis) {
                dis = temp;
                ret = (int)(it - ioqueue.begin());
            }
        }
        it++;
    }
    //printf("choose %d\n", ret);
    if (ret == -1) {
        ret = (int)(it - ioqueue.begin());
    }
    return ret;
}