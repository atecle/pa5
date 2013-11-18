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


typedef struct Customer Customer;

struct Customer {
    char *name;
    int id;  // key
    float debit;
    char *address;
    char *state;
    char *zip;
    UT_hash_handle hh;
    sem_t mutex;
};

void create_db(FILE *db, Customer **customers);
    

#endif
