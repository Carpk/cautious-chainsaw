#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "orderList.h"
#include "main.h"

/* takes head node, number of burgers and salads and adds them to linked list */
void addToList(order** head, char* name, int NumBurgers, int NumSalads, char* type) {
    order* currNode;
    currNode = *head;
    order* newNode;

    newNode = (order*)malloc(sizeof(order));
    newNode->name = name;
    newNode->salads = NumSalads;
    newNode->burgers = NumBurgers;
    strncpy(newNode->status, type, 8);
    newNode->next = NULL;

    if (currNode == NULL) {
        *head = newNode;
        return;
    }

    while(currNode->next != NULL) {
	if (debug) {
	    printf("Visiting node %s with values %d and %d\n", 
		currNode->name, currNode->burgers, currNode->salads);
	}
        currNode = currNode->next;
    }

    if (debug) {
        printf("Visiting node %s with values %d and %d\n",
            currNode->name, currNode->burgers, currNode->salads);
    }

    currNode->next = newNode;
}

/* takes head node and name, and returns boolean if found in list */
bool doesNameExist(order* head, char* name){
    order* currNode;
    currNode = head;

    while (currNode != NULL) {
        if (strcmp(currNode->name, name) == 0) {
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

/* takes head node and name, and returns boolean if 'not in' restuarant 
 * has been updated to 'in' */
bool updateStatus(order* head, char* name) {
    order* currNode = head;
    while (currNode != NULL) {
        if (strcmp(currNode->name, name) == 0) {
            if (strcmp(currNode->status, "not in") == 0) {
                strncpy(currNode->status, "in", 8);
                return true;
            } else {
                return false;
            }
        }
        currNode = currNode->next;
    }
    return false;
}

/* takes head node, number of burgers and salads and removes first matching or 
 * lower order amount from linked list */
char* retrieveAndRemove(order** head, int burgers, int salads) {
    char* name = NULL;
    bool showPreNode = true;
    order* currNode = *head;
    order* preNode = NULL;

    while (currNode != NULL) {
        bool enoughBurgers = currNode->burgers <= burgers;
        bool enoughSalads = currNode->salads <= salads;
        bool inRestuarant = strcmp(currNode->status, "in") == 0;

        if (debug && preNode != NULL) {
            if (showPreNode) {
                showPreNode = false;
                printf("Visiting node %s with values %d and %d\n",
                preNode->name, preNode->burgers, preNode->salads);
            }

            printf("Visiting node %s with values %d and %d\n",
                currNode->name, currNode->burgers, currNode->salads);
        }

        if (enoughBurgers && enoughSalads && inRestuarant) {
            if (preNode == NULL) {
               *head = currNode->next; 
            } else {
                preNode->next = currNode->next;
	    }
 
            name = currNode->name;
            free(currNode);

            return name;
        }

        preNode = currNode;
        currNode = currNode->next;
    }

    return name;
}

/* takes head node and name, and returns number of nodes in list before the named node */
int countOrdersAhead(order *head, char* name) {
    order* currNode = head;
    int count = 1;

    while (strcmp(currNode->name, name) != 0) {
        count++;
        currNode = currNode->next;
    }

    return count;
}

/* takes head node and name, and returns number of minutes (5 for burgers, 2 for salad)
 * in total that is ahead of the named node */
int displayWaitingTime(order *head, char* name) {
    order* currNode = head;
    int time = 0;

    while (strcmp(currNode->name, name) != 0) {
        if (debug) {
            printf("Visiting node %s with values %d and %d\n",
               currNode->name, currNode->burgers, currNode->salads);
        }

        time = time + (currNode->burgers * 5);
        time = time + (currNode->salads * 2);

        currNode = currNode->next;
    }

    return time;
}

/* takes head node and name, and traverses list while printing each node's info
 * up to the named node */
void displayOrdersAhead (order* head, char* name) {
    order* currNode = head;

    while (strcmp(currNode->name, name) != 0) {
        printf(" %s: %d burgers and %d salads \n",
               currNode->name, currNode->burgers, currNode->salads);
        currNode = currNode->next;
    }
}

/* takes head node, and traverses list while printing each node's info for all the nodes */
void displayListInformation(order *head) {
    order* currNode = head;
    while (currNode != NULL) {
        printf("%s: %d burgers and %d salads, currently %s the restaurant.\n",
               currNode->name, currNode->burgers, currNode->salads, currNode->status);
        currNode = currNode->next;
    }
}

