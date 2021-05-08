#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

//#include "includes/controller.h"

#include "includes/toyota.h"

//#include "includes/transmiter.h"

//rtl_433 -C si -R 59 -R 60 -R 82 -R 88 -R 89 -R 90 -R 95 -R 110 -R 120 -R 123 -p
int main(int argc, char *argv[]) {

    /*if(argc != 1){
        fprintf(stderr, "Numero de parametros incorrecto");
        exit(EXIT_FAILURE);
    }*/

    //struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"13\", \"id\" : \"8a58f9a2\", \"flags\" : 0, \"repeat\" : 1, \"pressure_kPa\" : 242.792, \"temperature_C\" : 15.000, \"maybe_battery\" : 56, \"mic\" : \"CHECKSUM\"}");
    
    //runController();
    //citroenTPMS("13", "8a58f9a2", 0x0, 1, 242.792, 15, 25);
    toyotaTPMS(128, "cafebabe",  40, 25);
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