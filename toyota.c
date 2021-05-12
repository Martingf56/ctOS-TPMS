
#include "includes/toyota.h"

char* toyotaTPMS(int status, char *id, float pressure, float temperature) {

    // full preamble is 0101 0101 0011 11 = 55 3c
    // could be shorter   11 0101 0011 11
    char *preamble = "01010101001111";

    /*Convert params data to binary*/
    char *systemStatus = dec2bin(status, 8);
    printf("Status: %s\n", systemStatus);
    char *systemID = dec2bin((long int)strtol(id, 0, 16), 32);
    printf("ID: %s\n", systemID);
    char *systemPressure = dec2bin((int)(PRESSURE_CONSTANT*(pressure + PRESSURE_OFFSET)), 8);
    printf("Press: %s\n", systemPressure);
    char *systemTemperature = dec2bin((int)(temperature + TEMPERATURE_OFFSET), 8);
    printf("Temp: %s\n", systemTemperature);

    char *onesFilled = "11111111";
    char *firstStatusBit = (char *)malloc(1+1);
    strncpy(firstStatusBit, systemStatus, 1);
    firstStatusBit[1]='\0';
    char *lastSevenStatusBits = (char *)malloc(7+1);
    strncpy(lastSevenStatusBits, systemStatus + 1, 7);

    char *invertedPressure = xor(systemPressure, onesFilled);

    char *frame = (char *)malloc(64+1);
    //char frame[64];
    strcpy(frame, systemID);
    strcat(frame, firstStatusBit);
    strcat(frame, systemPressure);
    strcat(frame, systemTemperature);
    strcat(frame, lastSevenStatusBits);
    strcat(frame, invertedPressure);
    printf("PressInv: %s\n", invertedPressure);
    printf("Trama: %s\n", frame);


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

    char *packetFormat = (char *)malloc(64+8+1);//Concatenate the frame with crc fo encode
    //char packetFormat[72];
    strcpy(packetFormat, frame);
    strcat(packetFormat, dec2bin(crc, 8));
    printf("crc: %s\n", dec2bin(crc, 8));
    printf("Trama + crc: %s\n", packetFormat);

    char *frameToModulate = differential_manchester_encoder(packetFormat);


    
    char lastBit[2];
    char finaltrail[4];
    strncpy(lastBit, frameToModulate + strlen(frameToModulate) - 1, strlen(frameToModulate)); //obtain the last bit
    if(!strcmp(lastBit, "1"))//we deny the last bit
        strcpy(finaltrail, "000");
    else
        strcpy(finaltrail, "111");
    printf("Trama Diferential Manchester: %s\n\n", frameToModulate);
    //lastBit[1]= '\0';
    printf("lastBit: %s\n\n", lastBit);

    
    
    /*strncpy(finaltrail, lastBit, 1);
    printf("finaltrail: %s\n", finaltrail);
    printf("lastBit: %s\n\n", lastBit);
    strcat(finaltrail, lastBit);
    printf("finaltrail: %s\n", finaltrail);
    printf("lastBit: %s\n\n", lastBit);
    strcat(finaltrail, lastBit);
    //finaltrail[3] = '\0';
    */
    printf("finaltrail: %s\n\n", finaltrail);
    
    //char *finalCodifiedFrame = (char *)malloc(166);
    char finalCodifiedFrame[162];
    strcpy(finalCodifiedFrame, preamble);
    strcat(finalCodifiedFrame, frameToModulate);
    strcat(finalCodifiedFrame, finaltrail);
    //strcat(finalCodifiedFrame, '\0');
    //finalCodifiedFrame[161]= '\0';
    /*Escritura o devolucion de la señal*/
    printf("%s\n%s\n", "Trama final Toyota",finalCodifiedFrame);
    //printf("%s\n%ld\n", "Tamaño total",strlen(finalCodifiedFrame));  
    
    return NULL;

}

/*
Trama final Toyota D 01010101001111001100110010110010101101010011010010110100110101010010110010110100101011010101010101010010110101010101010101001100110100110011001010110100110100111
Status: 10000011
ID: 11111011001001101010110001011010
Press: 00100000
Temp: 00101000
PressInv: 11011111
Trama: 1111101100100110101011000101101010010000000101000000001111011111
crc: 00101101
Trama + crc: 111110110010011010101100010110101001000000010100000000111101111100101101
Trama Diferential Manchester: 001100110010110010101101010011010010110100110101010010110010110100101011010101010101010010110101010101010101001100110100110011001010110100110100


Trama final Toyota I 01010101001111001100110010110010101101010011010010110100110101010010110010110100101011010101010101010010110101010101010101001100110100110011001010110100110100111
Status: 10000011
ID: 11111011001001101010110001011010
Press: 00100000
Temp: 00101000
PressInv: 11011111
Trama: 1111101100100110101011000101101010010000000101000000001111011111
crc: 00101101
Trama + crc: 111110110010011010101100010110101001000000010100000000111101111100101101
Trama Diferential Manchester: 001100110010110010101101010011010010110100110101010010110010110100101011010101010101010010110101010101010101001100110100110011001010110100110100
*/