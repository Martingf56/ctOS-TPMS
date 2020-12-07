#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "tpms_structs.h"

#define BUFFER_SIZE 1

#define READ_END 0
#define WRITE_END 1


void run(char *offset) {
    int pid, fd_pipe[2];
    char buff[BUFFER_SIZE], *signal_buff;

    if(pipe(fd_pipe)) {
        perror("Pipe failed");
        exit(-1);
    }

    pid = fork();
    if(pid == 0) {//child process
        char *args[] = {"sh", "-c", "rtl_433 -C si -F json", NULL};
        
        close(fd_pipe[READ_END]);
        dup2(fd_pipe[WRITE_END], STDOUT_FILENO);
        close(fd_pipe[WRITE_END]);

        if(execvp("/bin/sh", args) == -1){
            perror("Error when launching the program");
        }
    }
    else if(pid > 0){//parent process
        close(fd_pipe[WRITE_END]);
        while(1) {
            signal_buff = malloc(1000);
            strcpy(signal_buff, "");
            while (read(fd_pipe[READ_END], buff, 1)){
                //Generar el string
                strcat(signal_buff, buff);

                if(buff[0] == '\n') {
                    //Parsear string
                    struct tpms_general str = generalParser(signal_buff);
                    //Mostrar dinamicamente
                    printf("%s", signal_buff);
                    free(signal_buff);
                    signal_buff = malloc(1000);
                    strcpy(signal_buff, "");
                }

            }
        }
        free(signal_buff);
        close(fd_pipe[READ_END]);
    }
    else{
        perror("fork creation failed\n");
    }    
}

//rtl_433 -C si -R 59 -R 60 -R 82 -R 88 -R 89 -R 90 -R 95 -R 110 -R 120 -R 123 -p
int main(int argc, char *argv[]){

    /*if(argc != 1){
        fprintf(stderr, "Numero de parametros incorrecto");
        exit(EXIT_FAILURE);
    }*/

    run(argv[1]);

}
// struct tpms_general str = generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"fb26ac5a\",\"status\" : 131,\"pressure_kPa\" : 253.382,\"temperature_C\" : 14.000,\"mic\" : \"CRC\"}");

