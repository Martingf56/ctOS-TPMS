#include <string.h>
#include <stdlib.h>

#ifndef CONVERTER_H
#define CONVERTER_H

#include "converter.h"

#endif

#include "manchester_encoder.h"

#define PRESSURE_CONST 1.364 /*Constante por la que dividimos la presion*/

#define TEMP_OFFSET 50 /*Desplazamiento de la temperatura*/

void citroenTPMS(char* state, char *id, int flags, int repeat, float pressure, float temperature, int battery/*, char *filename*/){

    /*Preambulo: parte inicial de trama, indica el inicio de la comunicacion*/
    char* preamble = "01010101010101010101010101010110";

    /*finaltrail: parte final de trama, indica el final de la comunicacion*/
    char* finaltrail = "01111110";

    /*Trama a codificar*/
        /*conversion de datos a binario*/
    char* systemState = dec2bin((long int)strtol(state, 0, 16), 8);/*con strtol convertimos de hexadecimal a decimal*/
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
    

    /*Conversion de caracter a digito*/
    
    /*Calculo del checksum mediante la operacion xor entre elementos de la trama separados en grupos de 8 bits*/
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

    /*Construccion de la trama final que deberemos modular*/
    char* full_frame = (char*)malloc(80);  
    strcpy(full_frame, frame);
    
    strcat(full_frame, checksum);
    printf("%s %s\n", "Trama", full_frame);

    /*Codificacion de la señal en manchester*/
    char* manchester_frame = manchester_encoder(full_frame);
    printf("%s %s\n", "Trama Manchester", manchester_frame);

    /*Construccion de la trama codificada. El preambulo y el fin de la trama no se codifican*/
    char* finalCodifiedFrame = (char*)malloc(120);/*duda con el tamaño del preambulo*/
    strcpy(finalCodifiedFrame, preamble);
    strcat(finalCodifiedFrame, manchester_frame);
    strcat(finalCodifiedFrame, finaltrail);

    /*Escritura o devolucion de la señal*/
    printf("%s\n%s\n", "Trama final",finalCodifiedFrame);
    printf("%s\n%ld\n", "Tamaño total",strlen(finalCodifiedFrame));

}