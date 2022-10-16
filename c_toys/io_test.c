#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 512

int main(){
    //char buf[512];
    char * buf = (char *)malloc(BUFFSIZE);
    size_t len;
    while(1){
        getline(&buf, &len, stdin);  
        printf("getline: %s", buf);     

        fgets(buf, BUFFSIZE, stdin);
        printf("fgets: %s", buf);

        fscanf(stdin,"%s",buf);
        printf("fscanf: %s", buf);

        fscanf(stdin,"%s",buf);
        printf("fscanf: %s", buf);

        fscanf(stdin,"%s",buf);
        printf("fscanf: %s", buf);
    }
    free(buf);
    return 0;
}

