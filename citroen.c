
#include "includes/citroen.h"

char* citroenTPMS(char* state, char *id, int flags, int repeat, float pressure, float temperature, int battery/*, char *filename*/){

    /*Preamble: initial part of frame, indicates the start of communication*/
    char* preamble = "01010101010101010101010101010110";

    /*finaltrail: end part of frame, indicates the end of the communication*/
    char* finaltrail = "01111110";

    /*Frame to encode*/
        /*data conversion to binary*/
    char* systemState = dec2bin((long int)strtol(state, 0, 16), 8);/*with strtol we convert from hexadecimal to decimal*/
    char* systemID = dec2bin((long int)strtol(id, 0, 16), 32);
    char* systemFlags = dec2bin(flags, 4);
    char* systemRepeat = dec2bin(repeat, 4);
    char* systemPressure = dec2bin((int)(pressure/PRESSURE_CONST), 8);
    char* systemTemperature = dec2bin((int)(temperature + TEMP_OFFSET), 8);
    char* systemBattery = dec2bin(battery, 8);
    

    char* frame = (char*)malloc(72+1);/*hay que incluir un +1 para el '\0'??????*/
    strcpy(frame, systemState);
    strcat(frame, systemID);
    strcat(frame, systemFlags);
    strcat(frame, systemRepeat);
    strcat(frame, systemPressure);
    strcat(frame, systemTemperature);
    strcat(frame, systemBattery);
    

    /*Character to digit conversion*/
    
    /*Calculation of the checksum by means of the xor operation between elements of the frame separated into groups of 8 bits*/
    char* checksum = (char*)malloc(8);
    strncpy(checksum, frame, 8);

    char* groupBits = (char*)malloc(8);

    int i;
    int j = 0;
    for(i = 8; i < strlen(frame); i++){
        if (j == 8){
            checksum = xor(checksum, groupBits);
            j=0;
        }
        groupBits[j] = frame[i];
        j++;
    }  

    /*Construction of the final frame that we will have to modulate*/
    char* full_frame = (char*)malloc(80);  
    strcpy(full_frame, frame);
    
    strcat(full_frame, checksum);
    printf("%s %s\n", "Trama", full_frame);

    /*Signal encoding in manchester*/
    char* manchester_frame = manchester_encoder(full_frame);
    printf("%s %s\n", "Trama Manchester", manchester_frame);

    /*Construction of the coded frame. The preamble and the end of the frame are not encoded*/
    char* finalCodifiedFrame = (char*)malloc(120);/*duda con el tamaño del preambulo*/
    strcpy(finalCodifiedFrame, preamble);
    strcat(finalCodifiedFrame, manchester_frame);
    strcat(finalCodifiedFrame, finaltrail);

    /*Write or return the signal*/
    printf("%s\n%s\n", "Trama final",finalCodifiedFrame);
    printf("%s\n%ld\n", "Tamaño total",strlen(finalCodifiedFrame));    

    return finalCodifiedFrame;
}