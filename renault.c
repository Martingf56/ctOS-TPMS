
#include "includes/renault.h"
/*
Packet nibbles:
    F F/P PP TT II II II ?? ?? CC
- F = flags, (seen: c0: 22% c8: 14% d0: 31% d8: 33%) maybe 110??T
- P = Pressure, 10 bit 0.75 kPa
- I = id, 24-bit little-endian
- T = Temperature in C, offset -30
- ? = Unknown, mostly 0xffff
- C = Checksum, CRC-8 truncated poly 0x07 init 0x00
*/

char* renaultTPMS(char *id, float pressure, float temperature, int flags){
    
    char *preamble = "01010101010101010101010101010110";
    char* finaltrail = "0000";
    char* unknown = "1111111111111111";
    //unknown[16] = '\0';
    

    char flagsStr[2];
    sprintf(flagsStr, "%d", flags); 


    /*Convert params data to binary*/
    char *systemID = dec2bin((long int)strtol(id, 0, 16), 24);
    //printf("ID: %s\n", systemID);
    char* idLeft = (char*)malloc(8+1);
    strncpy(idLeft, systemID, 8);
    idLeft[8] = '\0';
    char* idMid = (char*)malloc(8+1);
    strncpy(idMid, systemID+8, 8);
    idMid[8] = '\0';
    char* idRight = (char*)malloc(8+1);
    strncpy(idRight, systemID+16, 8);
    idRight[8] = '\0';
    
    
    char* systemIDLittleEndian = (char*)malloc(24+1);
    strcpy(systemIDLittleEndian, idRight);
    //printf("IDLE1: %s\n", systemIDLittleEndian);
    strncat(systemIDLittleEndian, idMid, 8);
    //printf("IDLE2: %s\n", systemIDLittleEndian);
    strncat(systemIDLittleEndian, idLeft, 8);
    //printf("IDLE3: %s\n", systemIDLittleEndian);
    //systemIDLittleEndian[24] = '\0';
    //printf("IDLE: %s\n", systemIDLittleEndian);

    char *systemPressure = dec2bin((int)(pressure/PRESSURE_CONSTANT_RENAULT), 10);
    
    char *systemTemperature = dec2bin((int)(temperature + TEMPERATURE_OFFSET_RENAULT), 8);

    char* systemFlags = dec2bin((long int)strtol(flagsStr, 0, 16), 6);


    char* frame = (char*)malloc(64+1);
    strcpy(frame, systemFlags);
    strcat(frame, systemPressure);
    strcat(frame, systemTemperature);
    strcat(frame, systemIDLittleEndian);
    strcat(frame, unknown);
    
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
    uint8_t crc = crc8(crcFrame, 8, 0x07, 0x00);//Calculate crc of the frame
    
    char* full_frame = (char*)malloc(64+8+1);//Concatenate the frame with crc fo encode
    //char packetFormat[72];
    strcpy(full_frame, frame);
    strcat(full_frame, dec2bin(crc, 8));

    char* manchester_frame = manchester_encoder(full_frame);

    char* finalCodifiedFrame = (char*)malloc(180+1);
    strcpy(finalCodifiedFrame, preamble);
    strncat(finalCodifiedFrame, manchester_frame, 144);
    strcat(finalCodifiedFrame, finaltrail);
    finalCodifiedFrame[180]='\0';
    /*Escritura o devolucion de la señal*/
    printf("%s\n%s\n", "Trama final Renault",finalCodifiedFrame);
    printf("%s\n%ld\n", "Tamaño total",strlen(finalCodifiedFrame));    

    return finalCodifiedFrame;

}