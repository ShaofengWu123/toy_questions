#include <stdio.h>

int isPerfectSquare(int num){

    int threshold = 1;
    double x0 = num;
    int result = 0;

    if(num == 0 || num == 1){
        return 1;
    }

    // Newton Iteration to find an approx solution
    while(x0*x0 - num >= 1){
        x0 -= (x0*x0-num)/(2*x0);
    }
    result = (int)x0;
    if(result*result == num){
        return 1;
    }
    return 0;
}

int main(){

    printf("%d\n",isPerfectSquare(3));

    return 0;
}