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
Report *report = NULL;          //For final report print out


//Input: Categories of books separated by spaces. ex: "SPORTS01 POLITICS01 HISTORY01", taken from command line
//Creates hashtable of book categories


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

//adding into both Customer hashtable and Final Report Hashtable

void create_db(FILE *db) {
    
    char line[MAX_LEN];
    char *token;
    
    while (fgets(line, MAX_LEN, db)) {
        
        Customer *ctmr = NULL;
        Customer *f_ctmr = NULL;
        
        ctmr = (Customer*)malloc(sizeof(Customer));
        f_ctmr = (Customer*)malloc(sizeof(Customer));
        
        token = strtok(line, "|");
        strcpy(ctmr->name, token);
        strcpy(f_ctmr->name, token);
        token = strtok(NULL, "|");
        ctmr->id = atoi(token);
        f_ctmr->id = ctmr->id;
        
        token = strtok(NULL, "|");
        ctmr->debit = atof(token);
        f_ctmr->debit = ctmr->debit;
        
        token = strtok(NULL, "|");
        strcpy(ctmr->address, token);
        token = strtok(NULL, "|");
        strcpy(ctmr->state, token);
        token = strtok(NULL, "|");
        strcpy(ctmr->zip, token);
        
        pthread_mutex_init(&ctmr->mutex, NULL);
        
        Report *rep = NULL;
        rep = (Report*)malloc(sizeof(Report));
        rep->customer = f_ctmr;
        rep->cust_id = f_ctmr->id;
        rep->successes = NULL;
        rep->failures = NULL;
        pthread_mutex_init(&rep->lock, NULL);
        
        HASH_ADD_INT(customers, id, ctmr);
        HASH_ADD_INT(report, cust_id, rep);
    }
    
}


//to get rid new lines/tabs/etc while tokenizing

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
        order->cust_id = atoi(token);
        
        token = strtok(NULL, "|");
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
    
}

void enqueue(int index, Queue *order) {
    
    LL_APPEND(bookorders[index], order);
    Queue *ptr = bookorders[index];
    
    while (ptr->next != NULL) {
        ptr= ptr->next;
    }
    
}

Queue* dequeue(char *string) {
    Queue *ptr = NULL;
    Cat *temp = NULL;
    HASH_FIND_STR(cat, string, temp);
    if (temp == NULL)
    {
        return NULL;                                //exception
    }
    else
    {
        ptr = bookorders[temp->index];
        bookorders[temp->index] = bookorders[temp->index]->next;
    }
    return ptr;
    
}

void process_order(Queue *q) {
    
	Customer *tmp = NULL;
    Report *person = NULL;
    
	while (q != NULL) {
        Queue *qq = q->next;
        HASH_FIND_INT(customers, &(q->element->cust_id), tmp);
        HASH_FIND_INT(report, &(q->element->cust_id), person);
        
		if  ((tmp->debit - q->element->cost) > 0) {                     //success
    
            pthread_mutex_lock(&person->lock);
			pthread_mutex_lock(&tmp->mutex);
            
            
			tmp->debit = tmp->debit - q->element->cost;
            person->customer->debit = tmp->debit;
            q->amount = tmp->debit;
            Queue *ptr = q;
            
            
            LL_APPEND(person->successes, ptr);
			pthread_mutex_unlock(&tmp->mutex);
            pthread_mutex_unlock(&person->lock);
            
		} else {                                                        //failure
   
            pthread_mutex_lock(&person->lock);
            Queue *ptr = q;
            LL_APPEND(person->failures, ptr);
            pthread_mutex_unlock(&person->lock);   
		}

        q=qq;
        
        if (qq == NULL) break;
       
	}
}

void print_out() {
    
    FILE *fp = fopen("finalreport.txt", "w");

    Report *tmp1, *tmp2;
    
    HASH_ITER(hh, report, tmp1, tmp2) {
        fprintf(fp,"=== BEGIN CUSTOMER INFO ====\n");
        fprintf(fp,"### BALANCE ###\n");
        fprintf(fp,"Customer name: %s\n", tmp1->customer->name);
        fprintf(fp,"Remaining Balance: %.2f\n", tmp1->customer->debit);
        Queue *succ = tmp1->successes, *fail = tmp1->failures;
        fprintf(fp,"### SUCCESSFUL ORDERS ####\n");
        while (succ != NULL) {
            fprintf(fp,"%s | %.2f | %.2f\n", succ->element->title, succ->element->cost, succ->amount);
            succ = succ->next;
        }
        fprintf(fp,"### REJECTED ORDERS ###\n");
        while (fail != NULL) {
            fprintf(fp,"%s | %.2f\n", fail->element->title, fail->element->cost);
            fail = fail->next;
        }
        fprintf(fp,"=== END CUSTOMER INFO === \n\n");
    }
}

//useless 
void destroy_all(){
    Report *rtmp, *urtmp;
    Customer *ctmp, *uctmp;

    HASH_ITER(hh, customers, ctmp, uctmp){
        pthread_mutex_destroy(&ctmp->mutex);
    }
    HASH_ITER(hh, report, rtmp, urtmp){
        pthread_mutex_destroy(&report->lock);
    }
    free(cat);
    free(customers);
    free(report);
//    free(bookorders[100]);  test
}

