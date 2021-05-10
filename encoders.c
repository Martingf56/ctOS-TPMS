
#include "includes/encoders.h"

char* manchester_encoder(char* frame){
    char* manchester_frame = (char*)malloc(strlen(frame) * 2);
    strcpy(manchester_frame, ""); /*initialize to empty*/
    int i;
    for(i = 0; i < strlen(frame); i++){/*According to G.E. Thomas convention*/
        if(frame[i] == '0'){
            strcat(manchester_frame, "01");/*Low-high transition in the middle of the interval*/
        }
        else{
            strcat(manchester_frame, "10");/*High-low transition in the middle of the interval*/
        }
    }
    return manchester_frame;
}

char* differential_manchester_encoder(char* frame){
    char* differential_manchester_frame = (char*)malloc(strlen(frame) * 2);
    strcpy(differential_manchester_frame, ""); /*initialize to empty to be able to concatenate*/
    int i;
    char* lastBit = "1";

    for(i = 0; i < strlen(frame); i++){
        if(frame[i] == '1'){/*if it's 1, there is one transition only*/
            if(!strcmp(lastBit, "1")){
                strcat(differential_manchester_frame, "00");
                lastBit = "0";

            }
            else{
                strcat(differential_manchester_frame, "11");
                lastBit = "1";
            }
        }
        else{/*if it's 0, there is transition in the middle of the interval and also at the beginning*/
            if(!strcmp(lastBit, "1")){
                strcat(differential_manchester_frame, "01");
                lastBit = "1";
            }
            else{
                strcat(differential_manchester_frame, "10");
                lastBit = "0";
            }
        }
    }
    return differential_manchester_frame;
}
