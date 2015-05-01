//
//  CircularCircularElevator.cpp
//  IOScheduling
//
//  Created by Haoran Jia on 4/30/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#include "CircularElevator.h"
#include <climits>

int CircularElevator::nextUpFloor()
{
    int ret = -1;
    int dis = INT_MAX;
    for (deque<request>::iterator it = ioqueue.begin(); it->added; it++) {
        if (!it->finished && it->track >= head) {
            int temp = it->track - head;
            if (temp < dis) {
                dis = temp;
                ret = (int)(it - ioqueue.begin());
            }
        }
    }
    return ret;
}


int CircularElevator::nextRequest()
{
    int ret = -1;
    int low = 0;
    topTrack = -1;
    buttomTrack = INT_MAX;
    bool flag = false;
    deque<request>::iterator it = ioqueue.begin();
    while(it->added) {
        if (!it->finished) {
            flag = true;
            topTrack = it->track > topTrack ? it->track : topTrack;
            if (it->track < buttomTrack) {
                buttomTrack = it->track;
                low = (int)(it - ioqueue.begin());
            }
        }
        it++;
    }
    if (!flag) {
        it->added = true;
        return ret = nextRequest();
    }else{
        if (head <= topTrack) {
            ret = nextUpFloor();
        }else{
            ret = low;
        }
        return ret;
    }
}