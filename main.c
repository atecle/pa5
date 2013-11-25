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
    create_db(db);
    read_orders(orders); //main thread of execution acting as producer thread
    

    
    pthread_t thread_array[100];
    int id[100];
    
    int i = 0;
    
    for (cat; cat != NULL; cat = cat->hh.next) {
        int ord_index = cat->index;
        id[i] = pthread_create(&thread_array[i], NULL, (void*)&process_order, (void*)bookorders[ord_index]);
        i++;
    }
    
    int j;
    
    for (j = 0; j < i; j++) {
        pthread_join(thread_array[j], NULL);
    }
    
    print_out();
    
    return 1;
    
}
