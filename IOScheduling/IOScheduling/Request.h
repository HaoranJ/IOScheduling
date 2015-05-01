//
//  Request.h
//  IOScheduling
//
//  Created by Haoran Jia on 4/29/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#ifndef IOScheduling_Request_h
#define IOScheduling_Request_h

using namespace::std;

struct request
{
    int rid; //request id
    int stamp;
    int track;
    int issue;
    int finish;
    bool added;
    bool finished;
    
};
#endif
