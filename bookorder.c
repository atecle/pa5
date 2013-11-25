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
        Cat *item =  NULL;
        item = malloc(sizeof(Cat));
        char ret[strlen(token)];
        token = read_helper(token, ret);
        strcpy(item->category, token);
        item->index = index++;
        HASH_ADD_STR(cat, category, item);
    }
    
    for (i; i < 100; i++) {
        Queue *q = NULL;
        bookorders[i] = q;
    }
    
    
}


void create_db(FILE *db) {
    
    char line[MAX_LEN];
    char *token;
    
    while (fgets(line, MAX_LEN, db)) {
        
        Customer *ctmr = NULL;
        ctmr = (Customer*)malloc(sizeof(Customer));
        token = strtok(line, "|");
        strcpy(ctmr->name, token);
        token = strtok(NULL, "|");
        ctmr->id = atoi(token);
        token = strtok(NULL, "|");
        ctmr->debit = atof(token);
        token = strtok(NULL, "|");
        strcpy(ctmr->address, token);
        token = strtok(NULL, "|");
        strcpy(ctmr->state, token);
        token = strtok(NULL, "|");
        strcpy(ctmr->zip, token);
        HASH_ADD_INT(customers, id, ctmr);
        
    }
}

char* read_helper(char *s, char *ret) {
    
    int i, index = 0;
    for (i = 0; i < strlen(s); i++) {
        if (isalnum((int)s[i])) {
            ret[index] = s[i];
            index++;
        }
    }
    
    ret[index] = '\0';
    return ret;
}

void read_orders(FILE *orders) {
    
    
    int index = 0;
    char line[MAX_LEN];
    char *token;
    while (fgets(line, MAX_LEN, orders)) {
        
        Order *order = NULL;
        order = (Order*)malloc(sizeof(Order));
        
        token = strtok(line, "|");
        strcpy(order->title, token);
        
        token = strtok(NULL, "|");
        order->cost = atof(token);
        
        token = strtok(NULL, "|");
        order->quantity = atoi(token);
        
        token = strtok(NULL, "|");                                  //tokenized category has trailing space that will cause hash_find to return null
        char ret[strlen(token)];
        token = read_helper(token, ret);
        strcpy(order->category, token);
        
        Cat *temp = NULL;
        HASH_FIND_STR(cat, order->category, temp);
        if (temp == NULL) printf("WHAT\n");
        Queue *q = malloc(sizeof(Queue));
        q->element = order;
        enqueue(temp->index, q);
    }
    
   /* for (cat; cat!=NULL; cat= cat->hh.next) {
        int x = cat->index;
        printf("%s\n", bookorders[x]->element->category);
    }*/
    

    Queue *que = dequeue("HOUSING01");
       printf("Title: %s\t Cost: %f\t Quant: %d\t Cat: %s \n", que->element->title, que->element->cost, que->element->quantity, que->element->category);
    que = dequeue("HOUSING01");
    printf("Title: %s\t Cost: %f\t Quant: %d\t Cat: %s \n", que->element->title, que->element->cost, que->element->quantity, que->element->category);
    
   /* Cat *tmp=NULL;
    HASH_FIND_STR(cat, "HOUSING01", tmp);
    if (tmp == NULL) {
	    printf("who knows\n");
    }else{
	    printf("this is the int %d\n", tmp->index);
    } */
    
    
}

void enqueue(int index, Queue *order) {
    
    LL_APPEND(bookorders[index], order);
    
}

Queue* dequeue(char *string) {
    Queue *ptr = NULL;
    Cat *temp = NULL;
    HASH_FIND_STR(cat, string, temp);
    if (temp == NULL)
    {
        printf("SHIT\n");
        return NULL; //exception
    }
    else
    {
        printf("it works\n");
        ptr = bookorders[temp->index];
        bookorders[temp->index] = bookorders[temp->index]->next;
    //    LL_DELETE(ptr, q);
    }
        return ptr;
                        
}
                        
