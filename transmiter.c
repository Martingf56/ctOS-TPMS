#include "includes/transmiter.h"

char* encodeSignal(struct tpms_general tpms) {

    if (!strncmp(tpms.model, "Toyota", strlen("Toyota")))
        return toyotaTPMS(tpms.status, tpms.id, tpms.temperature_C, tpms.pressure_KPA);
    else if (!strncmp(tpms.model, "Citroen", strlen("Citrooen"))) 
        return citroenTPMS(tpms.state, tpms.id, tpms.flags, tpms.repeat, tpms.pressure_KPA, tpms.temperature_C, tpms.maybe_battery);

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
        if(execlp("python3", "python3", "./cc1101/cc1101.py", buff, NULL) == -1) {
            exit(-1);
        }
    }
    else if(pid > 0){
        int ret;
        close(pipe_fd[0]); //Close read side

        write(pipe_fd[1], encodeSignal(tpms), PIPE_BUFF_SIZE);//Send the dignal to the child
        
        while((ret = wait(&status)) > 0); //Wait for the child process

        close(pipe_fd[1]); //Close write side

        return ret != -1; // If ret is -1 the child not worked well
    }
    
    return false;
}

