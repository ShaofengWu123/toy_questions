#include <stdio.h>

void print_array_int(int* nums, int numsLen){
    for(int i=0;i<numsLen;i++){
        printf("%d ",nums[i]);
    }
    printf("\n");
}