
#include "includes/encoders.h"

char* manchester_encoder(char* frame){
    char* manchester_frame = (char*)malloc(strlen(frame) * 2);
    strcpy(manchester_frame, ""); /*inicializamos a vacio*/
    int i;
    for(i = 0; i < strlen(frame); i++){/*Segun IEEE 802.3*/
        if(frame[i] == '0'){
            strcat(manchester_frame, "10");/*Transicion alto-bajo en mitad del intervalo*/
        }
        else{
            strcat(manchester_frame, "01");/*Transicion bajo-alto en mitad del intervalo*/
        }
    }
    return manchester_frame;
}

char* differential_manchester_encoder(char* frame){
    char* differential_manchester_frame = (char*)malloc(strlen(frame) * 2);
    strcpy(differential_manchester_frame, ""); /*inicializamos a vacio para luego poder concatenarmanch*/
    int i;
    int bit_control;
    char* pattern;
    if(frame[0] == '0'){
        strcat(differential_manchester_frame, "01");
        pattern = "01";
    }
    else{
        strcat(differential_manchester_frame, "10");
        pattern = "10";
    }

    for(i = 1; i < strlen(frame); i++){
        if(frame[i] == '1'){/*si es 1, hay transición de alto-bajo o bajo-alto solo en mitad del intervalo, al principio no*/
            if(!strcmp(pattern, "01")){
                strcat(differential_manchester_frame, "10");
                pattern = "10";
            }
            else{
                strcat(differential_manchester_frame, "01");
                pattern = "01";
            }
        }
        else{/*si es 0, hay transicion en mitad del intervalo y tambien al principio*/
            strcat(differential_manchester_frame, pattern);
        }
    }
    return differential_manchester_frame;
}