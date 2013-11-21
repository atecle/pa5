//
//  bookorder.h
//  
//
//  Created by Adam on 11/14/13.
//
//

#ifndef _bookorder_h
#define _bookorder_h

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include "uthash.h"


struct Order {
    char *title;
    float cost;
    int quantity;
    char *category;
    pthread_mutex_t mutex;
};

struct Customer {
    char *name;
    int id;  // key
    float debit;
    char *address;
    char *state;
    char *zip;
    UT_hash_handle hh;
    pthread_mutex_t mutex;
};


typedef struct Customer Customer;
typedef struct Order Order;

void create_db(FILE *db, Customer **customers);

void read_orders(FILE *orders);

#endif
