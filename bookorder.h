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
typedef struct Order Order;
typedef struct Cat Cat;
typedef struct Queue Queue;

struct Cat {
    char *category;
    int index; // index in the Queue array
    UT_hash_handle hh; 
};

struct Queue {
    Order *element;
    Queue *prev;
    Queue *next;
};

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

void create_cat(char *categories);
void create_db(FILE *db);
void read_orders(FILE *orders);
Queue* dequeue(Queue *queue);
void enqueue(int index, Queue *order);


#endif
