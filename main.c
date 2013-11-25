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
  
    create_cat(argv[3]);
    //Customer *customers = NULL;
    create_db(db);
    
    //if (customers == NULL) printf("NULL\n");
    
    pthread_t thr1, thr2;
    
    read_orders(orders);
 
    //pthread_create(&thr1, NULL, (void*)&read_orders, (void*)orders);
    //pthread_join(thr1, NULL);
    
    return 1;
    
}
