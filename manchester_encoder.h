
#include <stdlib.h>
#include <string.h>


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