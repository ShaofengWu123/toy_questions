/* This is an example of using linux kernel queue macros  */
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _tailq_entry{
    int data;
    TAILQ_ENTRY(_tailq_entry) tailq_entry;
}tailq_entry;


int main()
{
    struct _tailq_entry entry1,entry2,entry3;
    entry1.data = 1;
    entry2.data = 2;
    entry3.data = 3;
    struct _tailq_entry *pentry;
    /* FIFO queue with tail queue */
    TAILQ_HEAD(tailq_head, _tailq_entry) head;
    TAILQ_INIT(&head);
    TAILQ_INSERT_TAIL(&head, &entry1, tailq_entry);
    TAILQ_INSERT_TAIL(&head, &entry2, tailq_entry);
    TAILQ_INSERT_TAIL(&head, &entry3, tailq_entry);

    while(!TAILQ_EMPTY(&head))
    {
        pentry = TAILQ_FIRST(&head);
        printf("%d ",pentry->data);
        TAILQ_REMOVE(&head, pentry, tailq_entry);
    }
    printf("\n");
    return 0;
}