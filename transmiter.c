#include "includes/transmiter.h"

//Return the emncode signal of the tpms struct
char* encodeSignal(struct tpms_general tpms) {

    //Compare with the vehicle name if is equal call his tpms generator signal and return on string the bits
    if (!strncmp(tpms.model, "Toyota", strlen("Toyota")))
        return toyotaTPMS(tpms.status, tpms.id, tpms.pressure_KPA, tpms.temperature_C);
    else if (!strncmp(tpms.model, "Citroen", strlen("Citroen"))) 
        return citroenTPMS(tpms.state, tpms.id, tpms.flags, tpms.repeat, tpms.pressure_KPA, tpms.temperature_C, tpms.maybe_battery);
    else if (!strncmp(tpms.model, "Renault", strlen("Renault"))) 
        return renaultTPMS(tpms.id, tpms.pressure_KPA, tpms.temperature_C, tpms.flags);

    return NULL;
}

bool transmitTPMSSignal(struct tpms_general tpms) {
    int pid, pipe_fd[2], status = 0;

    if (pipe(pipe_fd) == -1) {
        return false;
    }

    pid = fork();
    if (pid == 0) {//Child proccess
        char buff[PIPE_BUFF_SIZE];
        close(pipe_fd[1]); //Close write side
        read(pipe_fd[0], buff, PIPE_BUFF_SIZE);
        close(pipe_fd[0]);

        //Execute the program
        if(execlp("python3", "python3", "./cc1101/transmitCC1101.py", buff, NULL) == -1) {
            exit(-1);
        }
    }
    else if(pid > 0){
        int ret;
        close(pipe_fd[0]); //Close read side

        write(pipe_fd[1], encodeSignal(tpms), PIPE_BUFF_SIZE);//Send the dignal to the child
        
        wait(&status); //Wait for the child process

        close(pipe_fd[1]); //Close write side

        return ret != -1; // If ret is -1 the child not worked well
    }
    
    return false;
}

