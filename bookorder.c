//
//  bookorder->c
//
//
//  Created by Adam on 11/14/13.
//
//

#define MAX_LEN 1024
#include "bookorder.h"

Customer *customers = NULL;
Order **orderlist = NULL;
Cat *cat = NULL;


void create_cat(char *categories) {
    
    int index = 0;
    char *token = NULL;
    
    for (token = strtok(categories, " "); token != NULL; token = strtok(NULL, " ")) {
        Cat *item = malloc(sizeof(Cat));
        item->category = (char*)malloc(sizeof(char)*strlen(token));
        strcpy(item->category, token);
        item->index = index;
        HASH_ADD_STR(cat, category, item);
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

    int index = 0, size = 0;
    char line[MAX_LEN];
    char *token;
    
    while (fgets(line, MAX_LEN, orders)) size++;
    
    orderlist = malloc(sizeof(Order) * size);
    
    rewind(orders);
    
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
        orderlist[index] = order;
        index++;
    }
    int i, j;
    
    for (i = 0; i < index; i++) { //sort according to category. need to make less awful
        for (j = 0; j < index; j++) {
            if (strcasecmp(orderlist[i]->category, orderlist[j]->category) < 0) {
                Order *temp = orderlist[i];
                orderlist[i] = orderlist[j];
                orderlist[j] = temp;
            }
        }
    }
    
    printf("%s\n", orderlist[0]->category);
    
}

