//
//  queue.h
//  
//
//  Created by Adam on 11/21/13.
//
//

#ifndef _queue_h
#define _queue_h
#include "bookorder.h"

typedef Queue queue;

struct Queue {
    Order *element;
    Order *prev;
    Order *next;
}


#endif
