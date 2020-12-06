#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

char* removeQuotes(char *string){
    char* posIni = strchr(string,'"');
    char *ret = (char*)malloc(25);
    

    
    return string;
}


void assignValueStruct(char *key, char *value, struct tpms_general *signalStruct) {

    if(strcmp(key, "model")) 
        signalStruct->model = removeQuotes(value);
    else if(strcmp(key, "time")) 
        signalStruct->time = removeQuotes(value);
    else if(strcmp(key, "state")) 
        signalStruct->state = removeQuotes(value);
    else if(strcmp(key, "id")) 
        signalStruct->id = removeQuotes(value);
    else if(strcmp(key, "status")) 
        signalStruct->status = atoi(value);
    else if(strcmp(key, "flags")) 
        signalStruct->flags = atoi(value);
    else if(strcmp(key, "repeat")) 
        signalStruct->repeat = atoi(value);
    else if(strcmp(key, "pressure_kPa")) 
        signalStruct->pressure_KPA = atof(value);
    else if(strcmp(key, "temperature_C")) 
        signalStruct->temperature_C = atof(value);
    else if(strcmp(key, "maybe_battery")) 
        signalStruct->maybe_battery = atoi(value);
    
}


void parserElement(char *element, char *key, char *value) {
    char *element_aux = (char*)malloc(strlen(element));
    strcpy(element_aux, element);

    strcpy(key, removeQuotes(strtok(element_aux, " : ")));
    strcpy(value, strtok(NULL, " : "));

    free(element_aux);
}


struct tpms_general generalParser(char *signal) {
    char *element;
    struct tpms_general signalStruct;
    int i = 0;
    char *key = (char *)malloc(25);
    char *value = (char *)malloc(25);
    char *signal_aux = (char*)malloc(strlen(signal));

    strcpy(signal_aux, signal);
    element = strtok(signal_aux, ",");
    while (element != NULL) {
        
        //parserElement(element, key, value);
        //assignValueStruct(key, value, &signalStruct);
        element = strtok(NULL, ",");
    }
    
    free(signal_aux);
    return signalStruct;
}