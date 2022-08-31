#include <stdio.h>
#include <stdlib.h>

#define LEN 9

// 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。

int search(int* nums, int numsSize, int target){
    int head = 0;
    int tail = numsSize-1;
    int mid = 0;
    if(numsSize <= 0 || nums == NULL || target < nums[0] || target > nums[numsSize-1]){
        return -1;
    }   
    else{
        while(head <= tail){
            mid = (head + tail)/2;
            if(target == nums[mid]){
                return mid;
            }
            else if(target < nums[mid]){
                tail = mid - 1;
            }
            else{
                head = mid + 1;
            }
        }
        return -1;
    }
}


int main(){
    int nums[LEN] = {-23,-3,0,3,6,18,80,101,102};
    int result = 0;
    int target = -24;
    result = search(nums,LEN,target);
    printf("%d\n",result);
    return 0;
}