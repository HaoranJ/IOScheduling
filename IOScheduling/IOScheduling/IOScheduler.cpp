//
//  IOScheduler.cpp
//  IOScheduling
//
//  Created by Haoran Jia on 4/28/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#include "IOScheduler.h"
#include <cstdlib>

using namespace::std;

IOScheduler::IOScheduler()
{
    head = 0;
    time = 0;
    totalRequest = 0;
    numio = 0;
    finishCount = 0;
    upward = true;
    
    totalTime = 0;
    totalMove = 0;
    totalTurnAround = 0;
    totalWait = 0;
    maxWait = 0;
}

void IOScheduler::initRequest(string inputFile)
{
    ifstream readFile;
    readFile.open(inputFile.c_str());
    string line;
    int c = 0;
    while (getline(readFile, line)) {
        if(line[0] != '#')
        {
            int stamp, track;
            stringstream ss;
            ss<<line;
            ss >> stamp >> track;
            request req;
            req.rid = c++;
            req.stamp = stamp;
            req.track = track;
            req.added = false;
            req.finished = false;
            ioqueue.push_back(req);
            numio ++;
        }
    }
}

void IOScheduler::run(string inputFile, bool verbose)
{
    initRequest(inputFile);
    if(verbose) { printf("TRACE\n"); }
    time = ioqueue.begin()->stamp;
    ioqueue.begin()->added = true;
    
    if(verbose) { printf("%d:\t 0 add %d\n", time, ioqueue.begin()->track); }
    
    while (finishCount < numio) {
        int index = nextRequest();
        request& r = ioqueue[index];
        time = r.stamp > time ? r.stamp : time;
        r.issue = time;
        int trackNum = r.track;
        if (verbose) {
            printf("%d:%6d issue %d %d\n", time, index, trackNum, head);
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
                if(verbose) { printf("%d:%6d add %d\n", it->stamp, (int)(it - ioqueue.begin()), it->track); }
                it->added = true;
            }
        }
        r.finished = true;
        r.finish = time;
        finishCount ++;
        if(verbose) printf("%d:%6d finish %d\n", time, index, time - r.stamp);
    }
    
    if (verbose) {
        printf("IOREQS INFO\n");
        for (deque<request>::iterator it = ioqueue.begin(); it != ioqueue.end(); it++) {
            printf("%5d:%6d%6d%6d\n", (int)(it-ioqueue.begin()), it->stamp, it->issue, it->finish);
        }
    }
}

void IOScheduler::displayResults()
{
    printf("SUM: %d %d %.2lf %.2lf %d\n", totalTime,
           totalMove, (double)totalTurnAround/numio, (double)totalWait/numio, maxWait);
}