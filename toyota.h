#include <stdio.h>
#include <string.h>

#ifndef CONVERTER_H
#define CONVERTER_H

#include "converter.h"

#endif

#include "differential_manchester_encoder.h"

#define PRESSURE_CONSTANT 4
#define PRESSURE_OFFSET 7
#define TEMPERATURE_OFFSET 40

void toyotaTPMS(char *status, char *id, float pressure, float temperature) {

    // full preamble is 0101 0101 0011 11 = 55 3c
    // could be shorter   11 0101 0011 11
    char *preamble = "01010101001111";

    /*Convert params data to binary*/
    char *systemStatus = dec2bin(atoi(status), 8);
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

    char *packetFormat;// = frame crc

    char *frameToModulate = differential_manchester_encoder(packetFormat);

    char *lastBit = (char *)malloc(1);
    strncpy(lastBit, frameToModulate + strlen(frameToModulate) - 1, strlen(frameToModulate)); //obtain the last bit
    if(!strcmp(lastBit, "1"))//we deny the last bit
        strcpy(lastBit, "0");
    else
        strcpy(lastBit, "1");

    char *finaltrail = (char *)malloc(3);
    strcpy(finaltrail, lastBit);
    strcat(finaltrail, lastBit);
    strcat(finaltrail, lastBit);

    char *finalCodifiedFrame = (char *)malloc(90);
    strcpy(finalCodifiedFrame, preamble);
    strcat(finalCodifiedFrame, frameToModulate);
    strcat(finalCodifiedFrame, finaltrail);
    
}