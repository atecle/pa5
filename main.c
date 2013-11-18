//
//  main.c
//
//
//  Created by Adam on 11/14/13.
//
//

#include "bookorder.h"



int main(int argc, char **argv) {
    
    if (argc < 4) {
        printf("Incorrect number of inputs.");
        exit(0);
    }
    
    FILE *db, *orders;
    db = fopen(argv[1], "r");
    orders = fopen(argv[2], "r");
    
    if (!db || !orders) {
        printf("ERROR: File(s) not found");
        exit(0);
    }
    
    Customer *customers = NULL;
    create_db(db, &customers);
    
    for (customers; customers!=NULL; customers=customers->hh.next) {
        printf("User id: %d\tName: %s\n", customers->id, customers->name);
    }
    
    
}