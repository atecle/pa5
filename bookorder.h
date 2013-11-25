//
//  bookorder.h
//  
//
//  Created by Adam on 11/14/13.
//
//

#ifndef _bookorder_h
#define _bookorder_h

#define MAX_LEN 1024
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include "uthash.h"


typedef struct Customer Customer;
typedef struct Order Order;
typedef struct Cat Cat;
typedef struct Queue Queue;
typedef struct Report Report;

struct Cat {
    char category[MAX_LEN];         //easier to use uthash when string keys are static arrays not pointers
    int index;                      // index in the Queue array
    UT_hash_handle hh; 
};


struct Report {
    Customer *customer;
    int cust_id;                    //key
    Queue *successes;
    Queue *failures;
    UT_hash_handle hh;
};

struct Queue {                      //Queue is a linked list
    Order *element;
    Queue *next;
    float amount;
    pthread_mutex_t mutex;
};

struct Order {
    char title[MAX_LEN];
    float cost;
    int cust_id;
    char category[MAX_LEN];         // key
    pthread_mutex_t mutex;
};

struct Customer {
    char name[MAX_LEN];
    int id;                            // key
    float debit;
    char address[MAX_LEN];
    char state[MAX_LEN];
    char zip[MAX_LEN];
    UT_hash_handle hh;
    pthread_mutex_t mutex;
};

extern Cat *cat;
extern Queue *bookorders[];

void create_cat(char *categories);
void create_db(FILE *db);
void read_orders(FILE *orders);
Queue* dequeue(char *category);
void enqueue(int index, Queue *order);
char *read_helper(char *token, char *ret);
void process_order(Queue *queue);

#endif
