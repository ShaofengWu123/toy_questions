void counting_sort(int* nums, int numsLen, int head, int range, int flag){
    int* counter_array = (int *)malloc(range * sizeof(int));
    int j=0;
    int count_sum=0;

    if(!counter_array){
        printf("[Error] Not enough memory during counting sort!\n");
        return;
    } 
    if(numsLen <= 0){
        return;
    }
    //initilization 
    for(int i=0; i<range-1; i++){
        counter_array[i] = 0;
    }
    // count
    for(int i=0; i<numsLen; i++){
        counter_array[nums[i]-head]++; 
    }

    for(int i=0;i<range;i++){
        printf("%d ",counter_array[i]);
    }
    printf("\n");

    j = 0;
    if(flag == 1){// ascending
        for(int i=0; i<range; i++){
            
            count_sum += counter_array[i];
            for(;j<count_sum;j++){
                nums[j] = i+head;
            }
        }
    }
    
    else if(flag == 2){// descending         
        for(int i=range-1; i>=0; i--){
            count_sum += counter_array[i];
            for(;j<count_sum;j++){
                nums[j] = i+head;
            }
        }
    }
    // will be encapsulate to check flag
    // else{
    //     printf("Please specify");
    // }
    for(int i=0;i<numsLen;i++){
        printf("%d ",nums[i]);
    }
    printf("\n");

}

// int main(){
//     int nums[10] = {-20,-3,21,-6,1,13,13,10,-5,6};
//     counting_sort(nums,10,-20,30+20-1,2);

//     return 0;
// }