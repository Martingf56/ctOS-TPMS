#include <stdio.h>
#include <string.h>

#include "converter.h"

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




}