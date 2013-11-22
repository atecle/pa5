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

char* read_helper(char *s){
	char *ptr;
	char arr[strlen(s)];
	int index=0;
	for(ptr=s;*ptr!=NULL;ptr++){
		if(isalnum(ptr)!=0){
			arr[index] = ptr;
			index++;
		}
	}
	arr[index] = '\0';
	return arr;
}

void read_orders(FILE *orders) {
    char word[5] = read_helper(" words ");
    printf("%s\n", word);
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
        printf("Word: %s\t Len: %d\n", order->category, strlen(order->category));
        Cat *temp;
        HASH_FIND_STR(cat, order->category, temp);
        Queue *tmp = malloc(sizeof(Queue));
        tmp->element = order;
        if (temp == NULL) printf("NULL AS FUCK\n");
        //enqueue(temp->index, tmp);
        
    }
    
    int i;
    for ( i = 0; i < 6; i++) {
        if (bookorders[i] == NULL) {
            printf("i am null\n");
            continue;
        }
       printf(" %s\n", bookorders[i]->element->category);
    }
    
}

void enqueue(int index, Queue *order) {
    printf("I AM TESTING MY CODE\n");
    bookorders[index] = (Queue*)malloc(sizeof(Queue));
    printf("I HATE PTHREADS\n");
    DL_APPEND(bookorders[index], order);
    printf("I KNOW FORTRAN\n");
}

Queue* dequeue(Queue *queue) {
    
}

