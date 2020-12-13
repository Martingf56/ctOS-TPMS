
#include <stdlib.h>
#include <string.h>


char* manchester_encoder(char* frame){
    char* manchester_frame = (char*)malloc(strlen(frame) * 2);
    strcpy(manchester_frame, ""); /*inicializamos a vacio*/
    int i;
    for(i = 0; i < strlen(frame); i++){
        if(frame[i] == '1'){
            strcat(manchester_frame, "10");
        }
        else{
            strcat(manchester_frame, "01");
        }
    }
    return manchester_frame;
}