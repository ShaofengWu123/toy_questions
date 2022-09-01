// 给定一个无重复数字升序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

// 请必须使用时间复杂度为 O(log n) 的算法。

#include <stdio.h>
#include <stdlib.h>

#define LEN 9

int searchInsert(int* nums, int numsSize, int target){
    int mid = 0;
    int head = 0;
    int tail = numsSize-1;

    // if(numsSize<=0){
    //     return -1;
    // }

    if(target<nums[0]){
        return 0;
    }
    else if(target>nums[numsSize-1]){
        return numsSize;
    }

    while(head<=tail){
        mid = (head+tail)/2;
        if(target==nums[mid]){
            return mid;
        }
        else if(target<nums[mid]){
            tail = mid-1;
        }
        else{
            head = mid+1;
        }
    }
    // does not find the number
    return head;
}

int main(){
    int result = 0;
    int target = 1;
    int nums[LEN] = {-23,-4,-3,0,8,9,15,80,100};
    result = searchInsert(nums,LEN,target);
    printf("%d\n",result);
    return 0;
}

