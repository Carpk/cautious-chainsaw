#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct orderList { // queue
    char* name;
    int burgers;
    int salads;
    char status[8];
    struct orderList* next;
} order;

void addToList(order** head, char* name,int NumBurgers,int NumSalads, char* type);
bool doesNameExist(order* head, char* name);
bool updateStatus(order *head, char* name);
char* retrieveAndRemove(order** head, int burgers, int salads);
int countOrdersAhead(order *head, char* name);
int displayWaitingTime(order *head, char* name);
void displayOrdersAhead (order* head, char* name);
void displayListInformation(order *head);

