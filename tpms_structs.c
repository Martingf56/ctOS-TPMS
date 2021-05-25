#include "includes/tpms_structs.h"

struct tpms_general newFakeSignal(char *id, char *nameCar) {
    struct tpms_general tpms_signal;

    tpms_signal.id = (char*)malloc(strlen(id));
    strncpy(tpms_signal.id, id, strlen(id));
    tpms_signal.model = (char*)malloc(strlen(nameCar));
    strncpy(tpms_signal.model, nameCar, strlen(nameCar));

    //Fake values
    tpms_signal.temperature_C = 0;
    tpms_signal.pressure_KPA = 1;

    //Constant values Toyota
    if(!strncmp(nameCar, "Toyota", strlen("Toyota"))){
        tpms_signal.status = 131;
    }

    //Constant values Citroen
    if(!strncmp(nameCar, "Citroen", strlen("Citroen"))){
        tpms_signal.state = "13";
        tpms_signal.flags = 0;
        tpms_signal.maybe_battery = 56;
    }

    //Constant values Renault
    if(!strncmp(nameCar, "Renault", strlen("Renault"))){
        tpms_signal.flags = 34;
    }

    return tpms_signal;
}

void assignValueStruct(const char *key, const char *value, struct tpms_general *signalStruct) {
    //Compare the key, if the key is equal assign the value to the tpms struct
    if(!strncmp(key, "model", strlen("model"))) {
        //printf("%s %ld\n", value, strlen(value));
        signalStruct->model = (char*)malloc((strlen(value))+1);
        strncpy(signalStruct->model, value, strlen(value));
        signalStruct->model[strlen(value)] = '\0';
        
    }
    else if(!strncmp(key, "time", strlen("time"))) {
        //printf("%s %ld\n", value, strlen(value));
        signalStruct->time = (char*)malloc((strlen(value))+1);
        strcpy(signalStruct->time, value);
    }
    else if(!strncmp(key, "state", strlen("state"))) {
        signalStruct->state = (char*)malloc((strlen(value))+1);
        strcpy(signalStruct->state, value);
    }
    else if(!strncmp(key, "id", strlen("id"))) {
        signalStruct->id = (char*)malloc((strlen(value))+1);
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
        if(element[i] == '"') //Detect the first quotes
            open_quotes = !open_quotes;
        else  if(open_quotes)
            key[cont_key++] = element[i];//Recolect the chars of the key
        
        i++;
    }
    cont_value = 0; i++; open_quotes = false;
    while (i < strlen(element)) {
        if(element[i] == '"') {//Detect the first quotes
            if(!open_quotes) {
                strcpy(value, "");
                cont_value = 0;
            }
            open_quotes = !open_quotes;
        }
        else
            value[cont_value++] = element[i];//Recolect the chars of the value

        i++;
    }
}


struct tpms_general generalParser(char *signal) {
    char *element, *key ,*value;
    struct tpms_general signalStruct;
    char *signal_aux = (char*)malloc((strlen(signal))+1);

    strcpy(signal_aux, signal);
    element = strtok(signal_aux, ",");//Split the string
    
    while (element != NULL) {
        //Initialize the pointers
        key = (char*)malloc(KEY_VALUE_SIZE); 
        value = (char*)malloc(KEY_VALUE_SIZE);
        strncpy(key, "", KEY_VALUE_SIZE); strncpy(value, "", KEY_VALUE_SIZE); 
        
        parserElement(element, key, value);//Parser one single element
        assignValueStruct(key, value, &signalStruct);//Assign the value to the tpms struct
        
        element = strtok(NULL, ",");//Go to the next element
        
        free(key); free(value);//Liberate memory
    }
    
    free(signal_aux);
    return signalStruct;
}