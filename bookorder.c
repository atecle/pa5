//
//  bookorder->c
//
//
//  Created by Adam on 11/14/13.
//
//

#define MAX_LEN 1024
#include "bookorder.h"


void create_db(FILE *db, Customer **customers) {
    
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
        HASH_ADD_INT(*customers, id, ctmr);
        
    }
}

void read_orders(FILE *orders) {
    
    Order **orderlist = NULL;
    
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
    
    for (i = 0; i < index; i++) {
        for (j = 0; j < index; j++) {
            if (strcasecmp(orderlist[i]->category, orderlist[j]->category) < 0) {
                Order *temp = orderlist[i];
                orderlist[i] = orderlist[j];
                orderlist[j] = temp;
            }
        }
    }
    
    for (i = 0; i < index; i ++) {
        printf("%s\n", orderlist[i]->category);
    }
    printf("%d\n", index);
}
