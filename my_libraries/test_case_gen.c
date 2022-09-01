#include <stdlib.h>
#include "sort_algorithms.h"

/*
    @numsLen   Length of the sequence.
    @flag   0 for random, 1 for ascending, 2 for descending
    Returns the pointer to the sequence.
*/
int * generate_int_seq(int numsLen, int flag, int head, int tail){
    int * nums = NULL;
    int temp;
    if(numsLen <= 0){
        printf("[Error] Invalid sequence length: %d!\n",numsLen);
        return NULL;
    }
    else if(head >= tail){
        printf("[Error] Invalid sequence range: %d - %d\n", head, tail);
    }
    else{
        nums = (int *)malloc(numsLen * sizeof(int));
        if(!nums){
            printf("[Error] Not enough memory!\n");
            return NULL;
        }
        // generate random numbers
        for(int i=0; i < numsLen ; i++){
            temp = random()%(tail-head) + head;
            nums[i] = temp;
        }
        if(!flag){
            ;
        }
        else{
            counting_sort(nums, numsLen, head, tail-head+1, flag);
        }
        return nums;

    }
}