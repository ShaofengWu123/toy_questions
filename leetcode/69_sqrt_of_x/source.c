#include <stdio.h>

// 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。

// 由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

// int mySqrt(int x){
//     long long int head;
//     long long int tail;
//     long long int mid;
//     long long int result;
//     if(x==0 || x==1){
//         return x;
//     }
//     else{
//         head = 1;
//         tail = x;
//         while(head < tail){
//             mid = (head + tail)/2;
//             result = mid * mid;
//             if(result > x){
//                 tail = mid - 1;
//             }
//             else if(result < x){
//                 head = mid + 1;
//             }
//             else{
//                 return mid;
//             }
//         }
//         result = head * head;
//         if(result <= x){
//             return head;
//         }
//         else if(result > x){
//             return head-1;
//         }
//     }
// }

// Newton Iteration
int mySqrt(int x){
    int threshold = 1;
    double x0 = x;

    if(x==0){
        return x;
    }
    if(x==1 || x==2 || x==3){
        return 1;
    }
    
    while(x0*x0 - x > threshold){
        // calculate next x
        x0 -= (x0*x0-x)/(2*x0);  
    }

    return (int)x0;
}


int main(){
    printf("%d\n",mySqrt(1025));
    return 0;
}