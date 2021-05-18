
#include "includes/citroen.h"


/*
Packet nibbles:
    UU  IIIIIIII FR  PP TT BB  CC
- U = state, decoding unknown, not included in checksum
- I = id
- F = flags, (seen: 0: 69.4% 1: 0.8% 6: 0.4% 8: 1.1% b: 1.9% c: 25.8% e: 0.8%)
- R = repeat counter (seen: 0,1,2,3)
- P = Pressure (kPa in 1.364 steps, about fifth PSI?)
- T = Temperature (deg C offset by 50)
- B = Battery?
- C = Checksum, XOR bytes 1 to 9 = 0
*/
char* citroenTPMS(char* state, char *id, int flags, int repeat, float pressure, float temperature, int battery/*, char *filename*/){

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
    char* systemPressure = dec2bin((int)(pressure), 8);
    //printf("%i", (int)(pressure/PRESSURE_CONST));
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
    
    /*Calculo del checksum mediante la operacion xor entre elementos de la trama separados 
    en grupos de 8 bits sin tener en cuenta el state*/
    char* checksum = (char*)malloc(8+1);
    strncpy(checksum, frame + 8, 8);

    char* groupBits = (char*)malloc(8+1);

    int i;
    int j = 0;
    for(i = 16; i <= strlen(frame); i++){
        if (j == 8){
            checksum = xor(checksum, groupBits);
            j=0;
        }
        groupBits[j] = frame[i];
        j++;
    }  

    /*Construccion de la trama final que deberemos modular*/
    char* full_frame = (char*)malloc(80+1);  
    strcpy(full_frame, frame);
    
    strcat(full_frame, checksum);
    //printf("%s %s\n", "Trama", full_frame);

    /*Codificacion de la señal en manchester*/
    char* manchester_frame = manchester_encoder(full_frame);
    //printf("%s\n%s\n", "Trama Manchester", manchester_frame);
    //printf("%s\n%ld\n", "Tamaño total",strlen(manchester_frame));
    
    /*Construccion de la trama codificada. El preambulo y el fin de la trama no se codifican*/
    char* finalCodifiedFrame = (char*)malloc(200+1);
    strcpy(finalCodifiedFrame, preamble);
    strcat(finalCodifiedFrame, manchester_frame);
    strcat(finalCodifiedFrame, finaltrail);
    finalCodifiedFrame[200]='\0';
    /*Escritura o devolucion de la señal*/
    printf("%s\n%s\n", "Trama final Citroen",finalCodifiedFrame);
    printf("%s\n%ld\n", "Tamaño total",strlen(finalCodifiedFrame));    

    return finalCodifiedFrame;
}

/*
Trama final Citroen D
01010101010101010101010101010110010101100101101010010101100110010110011010010101101010101001011010011001010110010101010101010110010101010101011001011010010110010101101010010101100101010101101001111110
Trama final Citroen I
01010101010101010101010101010110010101100101101010010101100110010110011010010101101010101001011010011001010110010101010101010110010101010101011001011010010110010101101010010101100101010101101001111110
*/