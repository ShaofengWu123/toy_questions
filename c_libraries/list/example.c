/* This is an example of using linux kernel list macros  */
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _my_list
{
    struct list_head list;
}my_list;

typedef struct _my_list_entries{
    int data;
    struct list_head list_entry;    
}my_list_entry;


int main(){
    struct _my_list list1;
    struct _my_list_entries entry1,entry2,entry3;
    entry1.data = 1;
    entry2.data = 2;
    entry3.data = 3;

    struct _my_list_entries *pentry, *tmp;
	
    INIT_LIST_HEAD(&list1.list);

    list_add(&entry1.list_entry,&list1.list);
    list_add(&entry2.list_entry,&list1.list);
    list_add(&entry3.list_entry,&list1.list);

    list_for_each_entry_safe(pentry,tmp,&list1.list,list_entry){
        printf("%d ",pentry->data);
    }
    printf("\n");
    /* output: 3 2 1 */

    return 0;
}
