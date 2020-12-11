#include <math.h>
#include <stdlib.h>
#include <stdio.h>


char* dec2bin(long int c, int len) {
    int i;
    char* ret = (char*)malloc(len);
    strcpy(ret, "");
    for(i = len-1; i >= 0; i--){
        
        if((c & (1 << i)) != 0){
            strcat(ret, "1");
        }
        else{
            strcat(ret, "0");
        } 
    }
    return ret;
}

char* xor(char* check, char* next8bits){
    int i;
    char* ret = (char*)malloc(8);
    strcpy(ret, "");
    for(i = 0; i < 8; i++){
        if(check[i] == next8bits[i]){
            strcat(ret, "0");
        }
        else{
            strcat(ret, "1");
        }
    }
    return ret;
}