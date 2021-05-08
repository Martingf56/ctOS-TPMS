#include "includes/converter.h"

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

int bin2dec(char *bin, int len){
    int exp = 1, number = 0;
    
    for(int i = len - 1; i >= 0; i--) {
        if(bin[i] == '1')
            number += exp;
        exp *= 2;
    }

    return number;
}

char* xor(char* check, char* next8bits) {
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



char* and(char* check, char* next8bits) {
    int i;
    char* ret = (char*)malloc(8);
    char aca = '0';
    strcpy(ret, "");
    for(i = 7; i >= 0; i--){
        if(check[i] == next8bits[i]) {
            if(aca == '1')
                strcat(ret, "1");
            else
                strcat(ret, "0");
            
            if(check[i] == '1')
                aca = '1';
            else 
                aca = '0';
        }
        else{
            if(aca == '1')
                strcat(ret, "0");
            else
                strcat(ret, "1");
        }
    }
    printf("%s ^ %s = %s\n", check, next8bits, ret);
    return ret;
}