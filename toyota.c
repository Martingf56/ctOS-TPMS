
#include "includes/toyota.h"

void toyotaTPMS(int status, char *id, float pressure, float temperature) {

    // full preamble is 0101 0101 0011 11 = 55 3c
    // could be shorter   11 0101 0011 11
    char *preamble = "01010101001111";

    /*Convert params data to binary*/
    char *systemStatus = dec2bin(status, 8);
    char *systemID = dec2bin((long int)strtol(id, 0, 16), 32);
    char *systemPressure = dec2bin((int)(PRESSURE_CONSTANT*(pressure + PRESSURE_OFFSET)), 8);
    char *systemTemperature = dec2bin((int)(temperature + TEMPERATURE_OFFSET), 8);

    char *onesFilled = "11111111";
    char *firstStatusBit = (char *)malloc(1);
    strncpy(firstStatusBit, systemStatus, 1);
    char *lastSevenStatusBits = (char *)malloc(7);
    strncpy(lastSevenStatusBits, systemStatus + 1, 7);

    char *invertedPressure = xor(systemPressure, onesFilled);
    char *frame = (char *)malloc(64);
    strcpy(frame, systemID);
    strcat(frame, firstStatusBit);
    strcat(frame, systemPressure);
    strcat(frame, systemTemperature);
    strcat(frame, lastSevenStatusBits);
    strcat(frame, invertedPressure);


    //crc step
    uint8_t *crcFrame = (uint8_t *)malloc(strlen(frame));
    for(int i = 0; i < strlen(frame); i++) { /*Convert the string to a uint8 array*/
        crcFrame[i] = frame[i] - '0';
    }
    uint8_t crc = crc8(crcFrame, 8, 0x07, 0x80);//Calculate crc of the frame

    char *packetFormat = (char *)malloc(64+8);//Concatenate the frame with crc fo encode
    strcpy(packetFormat, frame);
    strcat(packetFormat, dec2bin(crc, 8));

    char *frameToModulate = differential_manchester_encoder(packetFormat);

    char *lastBit = (char *)malloc(1);
    strncpy(lastBit, frameToModulate + strlen(frameToModulate) - 1, strlen(frameToModulate)); //obtain the last bit
    if(!strcmp(lastBit, "1"))//we deny the last bit
        lastBit[0] = '0';
    else
        lastBit[0] = '1';

    char *finaltrail = (char *)malloc(3);
    strcpy(finaltrail, lastBit);
    strcat(finaltrail, lastBit);
    strcat(finaltrail, lastBit);

    char *finalCodifiedFrame = (char *)malloc(90);
    strcpy(finalCodifiedFrame, preamble);
    strcat(finalCodifiedFrame, frameToModulate);
    strcat(finalCodifiedFrame, finaltrail);
    
}