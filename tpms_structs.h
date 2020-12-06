#include <stdio.h>
#include <string.h>

struct tpms_general {
    char *model;
    char time[19];
    char *state;
    char id[8];
    int status;
    int flags;
    int repeat;
    float pressure_KPA;
    float temperature_C;
    int maybe_battery;
};


/*{
    "time" : "2020-12-04 13:04:21",
    "model" : "Citroen",
    "type" : "TPMS",
    "state" : "13",
    "id" : "8a58f9a2",
    "flags" : 0,
    "repeat" : 1,
    "pressure_kPa" : 242.792,
    "temperature_C" : 15.000,
    "maybe_battery" : 56,
    "mic" : "CHECKSUM"
}*/
void parserCitroen() {

}


/*{
    "time" : "2020-12-04 13:09:17",
    "model" : "Toyota",
    "type" : "TPMS",
    "id" : "fb26ac5a",
    "status" : 131,
    "pressure_kPa" : 253.382,
    "temperature_C" : 14.000,
    "mic" : "CRC"
}*/
void parserToyota() {

}

void parserElement(const char *element, char *type, char *definition) {
  
}


struct tpms_general generalParser(char *signal) {
    char *element;
    struct tpms_general signalStruct;
    int i = 0;

    while ((element = strtok(signal, ",")) != NULL) {
        //parserElement(element);
    }
    
}
//{ "time" : "2020-12-04 13:09:17"