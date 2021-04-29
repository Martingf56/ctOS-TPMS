
#include "includes/encoders.h"

char* manchester_encoder(char* frame){
    char* manchester_frame = (char*)malloc(strlen(frame) * 2);
    strcpy(manchester_frame, ""); /*initialize to empty*/
    int i;
    for(i = 0; i < strlen(frame); i++){/*According to IEEE 802.3*/
        if(frame[i] == '0'){
            strcat(manchester_frame, "01");/*High-low transition in the middle of the interval*/
        }
        else{
            strcat(manchester_frame, "10");/*Low-high transition in the middle of the interval*/
        }
    }
    return manchester_frame;
}

char* differential_manchester_encoder(char* frame){
    char* differential_manchester_frame = (char*)malloc(strlen(frame) * 2);
    strcpy(differential_manchester_frame, ""); /*initialize to empty to be able to concatenate*/
    int i;
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
        if(frame[i] == '1'){/*if it's 1, there is transition from high-low or low-high only in the middle of the interval, not at the beginning */
            if(!strcmp(pattern, "01")){
                strcat(differential_manchester_frame, "10");
                pattern = "10";
            }
            else{
                strcat(differential_manchester_frame, "01");
                pattern = "01";
            }
        }
        else{/*if it's 0, there is transition in the middle of the interval and also at the beginning*/
            strcat(differential_manchester_frame, pattern);
        }
    }
    return differential_manchester_frame;
}