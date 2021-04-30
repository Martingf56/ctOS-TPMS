#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "includes/controller.h"

//#include "includes/citroen.h"

#include "includes/transmiter.h"

//rtl_433 -C si -R 59 -R 60 -R 82 -R 88 -R 89 -R 90 -R 95 -R 110 -R 120 -R 123 -p
int main(int argc, char *argv[]) {

    /*if(argc != 1){
        fprintf(stderr, "Numero de parametros incorrecto");
        exit(EXIT_FAILURE);
    }*/

    struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"d2\", \"id\" : \"cafea1ba\", \"flags\" : 6, \"repeat\" : 3, \"pressure_kPa\" : 1, \"temperature_C\" : 0, \"maybe_battery\" : 16, \"mic\" : \"CHECKSUM\"}");
    
    runController();
    citroenTPMS(str.state, str.id, str.flags, str.repeat, str.pressure_KPA, str.temperature_C, str.maybe_battery);
    //toyotaTPMS("131", "fb26ac5a",  253.382, 14);
    //if(transmitTPMSSignal(str))
    //    printf("true");
}
//struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"fb26ac5a\",\"status\" : 131,\"pressure_kPa\" : 253.382,\"temperature_C\" : 14.000,\"mic\" : \"CRC\"}");
//struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"13\", \"id\" : \"8a58f9a2\", \"flags\" : 0, \"repeat\" : 1, \"pressure_kPa\" : 242.792, \"temperature_C\" : 15.000, \"maybe_battery\" : 56, \"mic\" : \"CHECKSUM\"}");
