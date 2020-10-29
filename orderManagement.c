#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "orderList.h"
#include "orderManagement.h"
#include "main.h"




void doAdd (order **head)
{
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0)
    {
        printf ("Error: Add command requires an integer value of at least 0\n");
        printf ("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }

    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0)
    {
        printf ("Error: Add command requires an integer value of at least 0\n");
        printf ("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }



    if (!doesNameExist(*head, name)) {
        printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
        addToList(head, name, NumBurgers, NumSalads, "in");
    } else {
        printf("An order with the given name already exists. Try another name.\n");
        free(name);
    }
}


void doCallAhead (order **head)
{
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 0\n");
        printf ("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }

    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 0\n");
        printf ("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }


    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }

    printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);


    if (!doesNameExist(*head, name)) {
        addToList(head, name, NumBurgers, NumSalads, "not in");
    } else {
        printf("No match found for the given name.Try again!\n");
        free(name);
    }
}

void doWaiting (order *head)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Wait command format: w <name>\n");
        return;
    }


    if (doesNameExist(head, name)) {
        printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
        updateStatus(head, name);
    } else {
        printf("No match found for the given name.Try again!\n");
    }

    free(name);
}

void doRetrieve (order** head)
{
    /* get info of prepared food ready on the counter from input */
    int PreparedBurgers = getPosInt();
    if (PreparedBurgers < 0)
    {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command format: r <# burgers> <# salads>\n");

        return;
    }

    int PreparedSalads = getPosInt();
    if (PreparedSalads < 0)
    {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command format: r <# burgers> <# salads>\n");
        return;
    }

    clearToEoln();
    printf ("Retrieve and remove the first group that can pick up the order of %d burgers and %d salads\n", 
	PreparedBurgers ,PreparedSalads);

    char* name;
    name = retrieveAndRemove(head, PreparedBurgers, PreparedSalads);
    
    if (name == NULL) {
        printf("No matching orders found.\n");
    } else {    
        free(name);
    }
}

void doList (order *head)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command format: l <name>\n");
        return;
    }

    if (doesNameExist(head, name)) {
        printf ("Order for \"%s\" is behind the following orders\n", name);
        displayOrdersAhead(head, name);
    } else {
        printf("No match found for the given name.Try again!\n");
    }

    free(name);
}

void doDisplay(order *head)
{
    clearToEoln();
    printf ("Display information about all orders\n");

    displayListInformation(head);
}


void doEstimateTime(order *head)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Time command requires a name to be given\n");
        printf ("Time command format: t <name>\n");
        return;
    }

    if (doesNameExist(head, name)) {
        int mins = displayWaitingTime(head, name);
        printf(" Estimated wait time for %s is %d minutes.\n", name, mins);
    } else {
        printf("No match found for the given name.Try again!\n");
    }

    free(name);
}

