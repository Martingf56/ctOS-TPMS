#include "includes/tpms_structs.h"

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