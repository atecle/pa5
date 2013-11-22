//
//  bookorder->c
//
//
//  Created by Adam on 11/14/13.
//
//

#define MAX_LEN 1024
#include "bookorder.h"
#include "utlist.h"

Customer *customers = NULL;
Cat *cat = NULL;
Queue *bookorders[100];

void create_cat(char *categories) {
    
    int index = 0, i = 0;
    char *token = NULL;
    
    for (token = strtok(categories, " "); token != NULL; token = strtok(NULL, " ")) {
        Cat *item = malloc(sizeof(Cat));
        item->category = (char*)malloc(sizeof(char)*strlen(token));
        strcpy(item->category, token);
        item->index = index++;
        HASH_ADD_STR(cat, category, item);
    }
    

    for (i; i < 100; i++) {
        bookorders[i] = NULL;
    }
    
   
}


void create_db(FILE *db) {
    
    char line[MAX_LEN];
    char *token;
    
    while (fgets(line, MAX_LEN, db)) {
        
        Customer *ctmr = NULL;
        ctmr = (Customer*)malloc(sizeof(Customer));
        token = strtok(line, "|");
        ctmr->name = (char*)malloc(sizeof(char) * strlen(token));
        strcpy(ctmr->name, token);
        token = strtok(NULL, "|");
        ctmr->id = atoi(token);
        token = strtok(NULL, "|");
        ctmr->debit = atof(token);
        token = strtok(NULL, "|");
        ctmr->address = (char*)malloc(sizeof(char)*strlen(token));
        strcpy(ctmr->address, token);
        token = strtok(NULL, "|");
        ctmr->state = (char*)malloc(sizeof(char)*strlen(token));
        strcpy(ctmr->state, token);
        token = strtok(NULL, "|");
        ctmr->zip = (char*)malloc(sizeof(char)*strlen(token));
        strcpy(ctmr->zip, token);
        HASH_ADD_INT(customers, id, ctmr);
        
    }
}

void read_orders(FILE *orders) {
    int index = 0;
    char line[MAX_LEN];
    char *token;
    while (fgets(line, MAX_LEN, orders)) {
        Order *order = NULL;
        order = (Order*)malloc(sizeof(Order));
        token = strtok(line, "|");
        order->title = malloc(sizeof(char) * strlen(token));
        strcpy(order->title, token);
        token = strtok(NULL, "|");
        order->cost = atof(token);
        token = strtok(NULL, "|");
        order->quantity = atoi(token);
        token = strtok(NULL, "|");
        order->category = (char*)malloc(sizeof(char) * strlen(token));
        strcpy(order->category, token);
        Cat *temp = NULL;
        HASH_FIND_STR(cat, order->category, temp);
        Queue *tmp = malloc(sizeof(Queue));
        tmp->element = order;
        enqueue(temp->index, tmp);
        
    }
    
    int i;
    for ( i = 0; i < 6; i++) {
        if (bookorders[i] == NULL) {
            printf("null\n");
            continue;
        }
       printf(" %s\n", bookorders[i]->element->category);
    }
    
}

void enqueue(int index, Queue *order) {
    bookorders[index] = (Queue*)malloc(sizeof(Queue));
    DL_APPEND(bookorders[index], order);
}

Queue* dequeue(Queue *queue) {
    
}

