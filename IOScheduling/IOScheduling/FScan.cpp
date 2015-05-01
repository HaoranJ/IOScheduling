//
//  FScan.cpp
//  IOScheduling
//
//  Created by Haoran Jia on 4/30/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#include "FScan.h"
#include <climits>
#include <cstdlib>

FScan::FScan()
{
    trace = false;
}

void FScan::run(string inputFile, bool verbose)
{
    initRequest(inputFile);
    trace = verbose;
    if(verbose) { printf("TRACE\n"); }
    time = ioqueue.begin()->stamp;
    ioqueue.begin()->added = true;
    activeQueue.push_back(* ioqueue.begin());
    if(verbose) { printf("%d:\t 0 add %d\n", time, ioqueue.begin()->track); }
    
    while (finishCount < numio) {
        int index = nextRequest();
        request& r = activeQueue[index];
        request& req = ioqueue[r.rid];
        time = r.stamp > time ? r.stamp : time;
        req.issue = time;
        int trackNum = r.track;
        if (verbose) {
            printf("%d:%6d issue %d %d\n", time, r.rid, trackNum, head);
        }
        
        int usedTime = abs(head - trackNum);
        totalMove += usedTime;
        totalTime = time + usedTime;
        int waitTime = time - r.stamp;
        totalWait += waitTime;
        maxWait = waitTime > maxWait ? waitTime : maxWait;
        time = time + usedTime;
        totalTurnAround += time - r.stamp;
        head = trackNum;
        
        for (deque<request>::iterator it = ioqueue.begin(); it != ioqueue.end(); it++) {
            if (it->stamp <= time && !it->added) {
                if(verbose) { printf("%d:%6d add %d\n", it->stamp, it->rid, it->track); }
                storeQueue.push_back(* it);
                it->added = true;
            }
        }
        req.finished = true; r.finished = true;
        req.finish = time;
        finishCount ++;
        if(verbose) printf("%d:%6d finish %d\n", time, r.rid, time - r.stamp);
    }
    
    if (verbose) {
        printf("IOREQS INFO\n");
        for (deque<request>::iterator it = ioqueue.begin(); it != ioqueue.end(); it++) {
            printf("%5d:%6d%6d%6d\n", (int)(it-ioqueue.begin()), it->stamp, it->issue, it->finish);
        }
    }

}

int FScan::nextUpFloor()
{
    int ret = -1;
    int dis = INT_MAX;
    for (deque<request>::iterator it = activeQueue.begin(); it != activeQueue.end(); it++) {
        if (!it->finished && it->track >= head) {
            int temp = it->track - head;
            if (temp < dis) {
                dis = temp;
                ret = (int)(it - activeQueue.begin());
            }
        }
    }
    return ret;
}

int FScan::nextDownFloor()
{
    int ret =-1;
    int dis = INT_MAX;
    for (deque<request>::iterator it = activeQueue.begin(); it != activeQueue.end(); it++) {
        if (!it->finished && it->track <= head) {
            int temp = head - it->track;
            if (temp < dis) {
                dis = temp;
                ret = (int)(it - activeQueue.begin());
            }
        }
    }
    return ret;
}

int FScan::nextRequest()
{
    int ret = -1;
    topTrack = -1;
    buttomTrack = INT_MAX;
    bool flag = false;
    deque<request>::iterator it = activeQueue.begin();
    while(it != activeQueue.end()) {
        if (!it->finished) {
            flag = true;
            topTrack = it->track > topTrack ? it->track : topTrack;
            buttomTrack = it->track < buttomTrack ? it->track : buttomTrack;
        }
        it++;
    }
    if (!flag) {
        if (storeQueue.size() == 0) {
            ioqueue[finishCount].added = true;
            storeQueue.push_back(ioqueue[finishCount]);
            if(trace) { printf("%d:%6d add %d\n", ioqueue[finishCount].stamp, it->rid, it->track); }
        }
        activeQueue.clear();
        activeQueue.swap(storeQueue);
        return ret = nextRequest();
    }else{
        //go down
        if (head > topTrack){
            if(upward) upward = false;
            ret = nextDownFloor();
        }else{ // go up
            if(!upward) upward = true;
            ret = nextUpFloor();
        }
        return ret;
    }
}