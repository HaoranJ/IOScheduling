//
//  SSTF.h
//  IOScheduling
//
//  Created by Haoran Jia on 4/29/15.
//  Copyright (c) 2015 Haoran Jia. All rights reserved.
//

#ifndef __IOScheduling__SSTF__
#define __IOScheduling__SSTF__

#include <stdio.h>
#include "IOScheduler.h"

class SSTF : public IOScheduler
{
public:
    int nextRequest();
};

#endif /* defined(__IOScheduling__SSTF__) */
