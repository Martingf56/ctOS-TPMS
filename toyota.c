
#include "includes/toyota.h"

char* toyotaTPMS(int status, char *id, float pressure, float temperature) {

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
    //printf("Trama: %s\n", frame);


    //crc step
    int offset = 0, len = 8;
    char str[8];
    uint8_t crcFrame[8]; 
    for(int i = 0; i < 8; i++) {
        strncpy(str, frame + offset, len);

        crcFrame[i] = bin2dec(str, len);
        /*bitsConvert += len;
        if(strlen(frame) - bitsConvert < len) {
            len = strlen(frame) - bitsConvert;
        }*/
        offset += len;
    }
    //uint8_t crcFrame[] = {0xca,0xfe, 0xba, 0xbe, 0xde, 0x20, 0x80, 0x43};
    uint8_t crc = crc8(crcFrame, 8, 0x07, 0x80);//Calculate crc of the frame

    char *packetFormat = (char *)malloc(64+8);//Concatenate the frame with crc fo encode
    strcpy(packetFormat, frame);
    strcat(packetFormat, dec2bin(crc, 8));
    //printf("Trama + crc: %s\n", packetFormat);

    char *frameToModulate = differential_manchester_encoder(packetFormat);


    char *lastBit = (char *)malloc(1);
    strncpy(lastBit, frameToModulate + strlen(frameToModulate) - 1, strlen(frameToModulate)); //obtain the last bit
    if(!strcmp(lastBit, "1"))//we deny the last bit
        lastBit[0] = '0';
    else
        lastBit[0] = '1';
    //printf("Trama Diferential Manchester: %s\n\n", frameToModulate);
    lastBit[1]= '\0';


    char finaltrail[3];
    strncpy(finaltrail, lastBit, 1);
    strcat(finaltrail, lastBit);
    strcat(finaltrail, lastBit);
    
    char *finalCodifiedFrame = (char *)malloc(161);
    strcpy(finalCodifiedFrame, preamble);
    strcat(finalCodifiedFrame, frameToModulate);
    strcat(finalCodifiedFrame, finaltrail);

    /*Escritura o devolucion de la señal*/
    //printf("%s\n%s\n", "Trama final",finalCodifiedFrame);
    //printf("%s\n%ld\n", "Tamaño total",strlen(finalCodifiedFrame));  
    
    return NULL;

}