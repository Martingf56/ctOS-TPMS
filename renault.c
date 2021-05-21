
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

    char flagsStr[2];
    sprintf(flagsStr, "%d", flags); 

    char idLeft[9], idMid[9], idRight[9];

    /*Convert params data to binary*/
    char *systemID = dec2bin((long int)strtol(id, 0, 16), 24);
    //printf("ID: %s\n", systemID);

    strncpy(idLeft, systemID, 8);
    idLeft[8] = '\0';
    strncpy(idMid, systemID+8, 8);
    idMid[8] = '\0';
    strncpy(idRight, systemID+16, 8);
    idRight[8] = '\0';
    
    
    char systemIDLittleEndian[25];
    strcpy(systemIDLittleEndian, idRight);
    strcat(systemIDLittleEndian, idMid);
    strcat(systemIDLittleEndian, idLeft);
    systemIDLittleEndian[24] = '\0';
    //printf("IDLE: %s\n", systemIDLittleEndian);

    char *systemPressure = dec2bin((int)(pressure/PRESSURE_CONSTANT_RENAULT), 10);
    //printf("Press: %s\n", systemPressure);
    char *systemTemperature = dec2bin((int)(temperature + TEMPERATURE_OFFSET_RENAULT), 8);
    //printf("Temp: %s\n", systemTemperature);
    char* systemFlags = dec2bin((long int)strtol(flagsStr, 0, 16), 6);
    //printf("Flags: %s\n", systemFlags);
    char *unknown = "1111111111111111";
    //printf("Unknown: %s\n", unknown);

    char frame[65];
    //char frame[64];
    strcpy(frame, systemFlags);
    strcat(frame, systemPressure);
    strcat(frame, systemTemperature);
    strcat(frame, systemIDLittleEndian);
    strcat(frame, unknown);
    frame[64] = '\0';
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
    uint8_t crc = crc8(crcFrame, 8, 0x07, 0x00);//Calculate crc of the frame

    char full_frame[73];//Concatenate the frame with crc fo encode
    //char packetFormat[72];
    strcpy(full_frame, frame);
    strcat(full_frame, dec2bin(crc, 8));
    //printf("crc: %s\n", dec2bin(crc, 8));
    full_frame[72] = '\0';
    //printf("Trama + crc: %s\n", full_frame);
    //printf("%s\n%ld\n", "Tamaño total",strlen(full_frame));

    char* manchester_frame = manchester_encoder(full_frame);
    //printf("%s\n%s\n", "Trama Manchester", manchester_frame);
    //printf("%s\n%ld\n", "Tamaño total",strlen(manchester_frame));

    char* finalCodifiedFrame = (char*)malloc(200+1);
    strcpy(finalCodifiedFrame, preamble);
    strcat(finalCodifiedFrame, manchester_frame);
    strcat(finalCodifiedFrame, finaltrail);
    finalCodifiedFrame[200]='\0';
    /*Escritura o devolucion de la señal*/
    printf("%s\n%s\n", "Trama final Renault",finalCodifiedFrame);
    printf("%s\n%ld\n", "Tamaño total",strlen(finalCodifiedFrame));    

    return finalCodifiedFrame;

}