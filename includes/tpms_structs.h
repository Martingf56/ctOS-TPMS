#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define KEY_VALUE_SIZE 25

struct tpms_general {
    char *model;
    char *time;
    char *state;
    char *id;
    int status;
    int flags;
    int repeat;
    float pressure_KPA;
    float temperature_C;
    int maybe_battery;
};

struct tpms_general newFakeSignal(char *id, char *nameCar);

void assignValueStruct(const char *key, const char *value, struct tpms_general *signalStruct);

void parserElement(char *element, char *key, char *value);

struct tpms_general generalParser(char *signal);

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