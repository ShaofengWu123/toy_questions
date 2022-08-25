#include <stdio.h>
#include <stdlib.h>

#define LEN 16

void max_subarray(int * a, int len){
    int head = 0; 
    int tail = 0;
    int max_head = 0;
    int max_tail = 0;
    int sum = a[0];
    int prefix_sum = sum;
    /* scan */
    while(tail<len-1){
        tail++;
        if(prefix_sum>=0){
            /* if prefix_sum is not negative, add next element to prefix_sum */
            prefix_sum += a[tail];
            /* check if prefix_sum is larger than sum */
            if(prefix_sum > sum){
                max_head = head;
                max_tail = tail;
                sum = prefix_sum;
            }
            else{;}
        }
        /* if prefix_sum is negative, re-start the calculation of prefix_sum */
        else{
            head = tail;
            prefix_sum = a[head];        
        }
    }
    /* print result */
    printf("Max Subarray\nHead Index: %d\nTail Index: %d\nMax Sum: %d\n",max_head,max_tail,sum);
}

int main(){
    int test_case[LEN] =  {3,4,-8,26,
                            1,-12,-17,13,
                            22,4,-8,-21,
                            12,15,0,-8};
    max_subarray(test_case,LEN);

    return 0;
}