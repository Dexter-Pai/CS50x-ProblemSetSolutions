#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    node *list = NULL;
    node *n = malloc(sizeof(node));
    n->number = atoi(argv[1]);
    (*n).next = NULL;
    list = n;

    n = malloc(sizeof(node));
    n->number = atoi(argv[2]);
    // this is for queue
    // list->next = n;
    // (*n).next = NULL;

    // the below lines are for stack, these can interchange with queue to have different effect
    n->next = list;
    list = n;

    //iterating is apparently the same for both queue and stack methods
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }
}