#include "includes/transmiter.h"

bool transmitTPMSSignal(struct tpms_general tpms) {
    //Need pipes

    int pid = fork();
    if (pid == 0){//Child proccess
        //Wait to receive the signal an then call the pyhton code of cc1101
    }
    else if(pid > 0){
        //Send with pipe the signal to the child and then wait until finish
    }
    else {

    }

    
    return false;
}

char* encodeSignal(struct tpms_general tpms) {

    if (!strncmp(tpms.model, "Toyota", strlen("Toyota"))) {
        toyotaTPMS(tpms.status, tpms.id, tpms.temperature_C, tpms.pressure_KPA);
        return "";
    }
    else if (!strncmp(tpms.model, "Citroen", strlen("Citrooen"))) {
        citroenTPMS(tpms.state, tpms.id, tpms.flags, tpms.repeat, tpms.pressure_KPA, tpms.temperature_C, tpms.maybe_battery);
        return "";
    }
}