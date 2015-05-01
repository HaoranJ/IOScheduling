//
//  main.cpp
//  IOScheduling
//
//  Created by Haoran Jia on 4/28/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <string>
#include <cstdlib>

#include "IOScheduler.h"
#include "FCFS.h"
#include "SSTF.h"
#include "Elevator.h"
#include "CircularElevator.h"
#include "FScan.h"

using namespace::std;

int main(int argc, char * argv[]) {
    int c;
    bool verbose = false;
    string algo = "";
    while((c = getopt (argc, argv, "vs:")) != -1){
        if (c == 'v') {
            verbose = true;
        }
        else if (c == 's') {
            algo = optarg;
        }
    }
    string inputFile = argv[optind];
    IOScheduler * iosched;
    if(algo == "i") { iosched = new FCFS(); }
    else if(algo == "j") { iosched = new SSTF(); }
    else if(algo == "s") { iosched = new Elevator(); }
    else if(algo == "c") { iosched = new CircularElevator(); }
    else if(algo == "f") {
        FScan * f = new FScan();
        f->run(inputFile, verbose);
        f->displayResults();
        return 0;
    }
    iosched->run(inputFile, verbose);
    iosched->displayResults();
    return 0;
}
