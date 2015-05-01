//
//  Elevator.cpp
//  IOScheduling
//
//  Created by Haoran Jia on 4/30/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//
#include <climits>
#include "Elevator.h"

int Elevator::nextUpFloor()
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

int Elevator::nextDownFloor()
{
    int ret =-1;
    int dis = INT_MAX;
    for (deque<request>::iterator it = ioqueue.begin(); it->added; it++) {
        if (!it->finished && it->track <= head) {
            int temp = head - it->track;
            if (temp < dis) {
                dis = temp;
                ret = (int)(it - ioqueue.begin());
            }
        }
    }
    return ret;
}

int Elevator::nextRequest()
{
    int ret = -1;
    topTrack = -1;
    buttomTrack = INT_MAX;
    bool flag = false;
    deque<request>::iterator it = ioqueue.begin();
    while(it->added) {
        if (!it->finished) {
            flag = true;
            topTrack = it->track > topTrack ? it->track : topTrack;
            buttomTrack = it->track < buttomTrack ? it->track : buttomTrack;
        }
        it++;
    }
    if (!flag) {
        it->added = true;
        return ret = nextRequest();
    }else{
        
        if ((upward && head <= topTrack) || (!upward && head < buttomTrack)) {
            if(!upward) upward = true;
            ret = nextUpFloor();
        }else{
            if(upward) upward = false;
            ret = nextDownFloor();
        }
        return ret;
    }
}