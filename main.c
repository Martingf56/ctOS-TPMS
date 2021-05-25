#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "includes/controller.h"

#include "includes/toyota.h"
#include "includes/renault.h"
#include <math.h>
//#include "includes/transmiter.h"

//rtl_433 -C si -R 59 -R 60 -R 82 -R 88 -R 89 -R 90 -R 95 -R 110 -R 120 -R 123 -p
int main(int argc, char *argv[]) {

    /*if(argc != 1){
        fprintf(stderr, "Numero de parametros incorrecto");
        exit(EXIT_FAILURE);
    }*/
    
    //struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"d2\", \"id\" : \"cafea1ba\", \"flags\" : 6, \"repeat\" : 3, \"pressure_kPa\" : 1, \"temperature_C\" : 0, \"maybe_battery\" : 16, \"mic\" : \"CHECKSUM\"}");
    //struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"13\", \"id\" : \"8a58f9a2\", \"flags\" : 0, \"repeat\" : 1, \"pressure_kPa\" : 242.792, \"temperature_C\" : 15.000, \"maybe_battery\" : 56, \"mic\" : \"CHECKSUM\"}");
    //struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"cafebabe\",\"status\" : 128,\"pressure_kPa\" : 40,\"temperature_C\" : 25,\"mic\" : \"CRC\"}");
    //struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"fb26ac5a\",\"status\" : 131,\"pressure_kPa\" : 253.382,\"temperature_C\" : 14.000,\"mic\" : \"CRC\"}");
    
    runController();
    //citroenTPMS(str.state, str.id, str.flags, str.repeat, 1, 0, str.maybe_battery);
    /*citroenTPMS("13", "8a58f9a2", 0, 1, 1, 0, 56);
    toyotaTPMS(131, "fb26ac5a",  1, 0);
    renaultTPMS("87f293", 1, 0, 34);
    */
    //renaultTPMS("87f293", 1, 0, 34);
    //toyotaTPMS(str.status, str.id,  1, 0);
    /*str = generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"13\", \"id\" : \"8a58f9a2\", \"flags\" : 0, \"repeat\" : 1, \"pressure_kPa\" : 242.792, \"temperature_C\" : 15.000, \"maybe_battery\" : 56, \"mic\" : \"CHECKSUM\"}");
    citroenTPMS(str.state, str.id, str.flags, str.repeat, 1, 0, str.maybe_battery);
    renaultTPMS("87f293", 1, 0, 34);
    */
    //if(transmitTPMSSignal(str))
    //    printf("true");

}
//struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"fb26ac5a\",\"status\" : 131,\"pressure_kPa\" : 253.382,\"temperature_C\" : 14.000,\"mic\" : \"CRC\"}");
//struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"13\", \"id\" : \"8a58f9a2\", \"flags\" : 0, \"repeat\" : 1, \"pressure_kPa\" : 242.792, \"temperature_C\" : 15.000, \"maybe_battery\" : 56, \"mic\" : \"CHECKSUM\"}");
/*
    int init = 50, bitsConvert = 0, len = 8;
    char* frame = "1100101011111110000000010011011000100011100111000101001000";
    char* str = (char *)malloc(8);
    uint8_t crcFrame[8]; //= {0x3,0x2b,0xf8,0x4,0xD8,0x8e,0x71,0x48};
    for(int i = 7; i >= 0; i--) {
        strncpy(str, frame + init, len);
        
        crcFrame[i] = bin2dec(str, len);

        bitsConvert += len;
        if(strlen(frame) - bitsConvert < len) {
            len = strlen(frame) - bitsConvert;
        }
        init -= len;
    }
    uint8_t crc = crc8(crcFrame, 8, 0x13, 0x00);//Calculate crc of the frame
    printf("\n%d\n", crc);
    printf("%s\n", differential_manchester_encoder("11100101011111110000000010011011000100011100111000101001000000000111"));//000000001001011101101000100000
*/


/*
010101010101010101010101010101101010011001010101010101010101011001010110101010011001010101101010101010100101100110010110010110101010101010101010101010101010101001010101101001100000

01010101010101010101010101010110 10100110 01010101 01010101 010101100101011010101001100101010110101010101010010110011001011001011010101010101010101010101010101010100101010110100110 0000
*/

/*
F     F/P  PP       TT       II       II       II       ??       ??       CC
1101 00 00 00000001 00011110 10000111 11110010 10010011 11111111 11111111 00001101
b0         b1       b2       b3       b4       b5       b6       b7       b8
*/