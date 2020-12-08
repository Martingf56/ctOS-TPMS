#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define KEY_VALUE_SIZE 25

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

void assignValueStruct(const char *key, const char *value, struct tpms_general *signalStruct) {

    if(!strncmp(key, "model", strlen("model"))) {
        signalStruct->model = (char*)malloc(strlen(value));
        strcpy(signalStruct->model, value);
    }
    else if(!strncmp(key, "time", strlen("time"))) {
        signalStruct->time = (char*)malloc(strlen(value));
        strcpy(signalStruct->time, value);
    }
    else if(!strncmp(key, "state", strlen("state"))) {
        signalStruct->state = (char*)malloc(strlen(value));
        strcpy(signalStruct->state, value);
    }
    else if(!strncmp(key, "id", strlen("id"))) {
        signalStruct->id = (char*)malloc(strlen(value));
        strcpy(signalStruct->id, value);
    }
    else if(!strncmp(key, "status", strlen("status"))) 
        signalStruct->status = atoi(value);
    else if(!strncmp(key, "flags", strlen("flags"))) 
        signalStruct->flags = atoi(value);
    else if(!strncmp(key, "repeat", strlen("repeat"))) 
        signalStruct->repeat = atoi(value);
    else if(!strncmp(key, "pressure_kPa", strlen("pressure_kPa"))) 
        signalStruct->pressure_KPA = atof(value);
    else if(!strncmp(key, "temperature_C", strlen("temperature_C"))) 
        signalStruct->temperature_C = atof(value);
    else if(!strncmp(key, "maybe_battery", strlen("maybe_battery"))) 
        signalStruct->maybe_battery = atoi(value);

}


void parserElement(char *element, char *key, char *value) {
    bool open_quotes = false;
    int cont_value;

    int i = 0, cont_key = 0;
    while(i < strlen(element) && element[i] != ':') {
        if(element[i] == '"') 
            open_quotes = !open_quotes;
        else  if(open_quotes)
            key[cont_key++] = element[i];
        
        i++;
    }
    cont_value = 0; i++; open_quotes = false;
    while (i < strlen(element)) {
        if(element[i] == '"') {
            if(!open_quotes) {
                strcpy(value, "");
                cont_value = 0;
            }
            open_quotes = !open_quotes;
        }
        else
            value[cont_value++] = element[i];

        i++;
    }
}


struct tpms_general generalParser(char *signal) {
    char *element, *key ,*value;
    struct tpms_general signalStruct;
    int i = 0;
    char *signal_aux = (char*)malloc(strlen(signal));

    strcpy(signal_aux, signal);
    element = strtok(signal_aux, ",");
    while (element != NULL) {
        key = (char*)malloc(KEY_VALUE_SIZE); value = (char*)malloc(KEY_VALUE_SIZE);
        parserElement(element, key, value);
        assignValueStruct(key, value, &signalStruct);
        element = strtok(NULL, ",");
        free(key); free(value);
    }
    
    free(signal_aux);
    return signalStruct;
}