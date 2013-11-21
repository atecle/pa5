//
//  queue.c
//  
//
//  Created by Adam on 11/21/13.
//
//

#include "utlist.h"

void push(Order *head, Order *order) {
    DL_APPEND(head, order);
}
