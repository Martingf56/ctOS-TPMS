#include "includes/controller.h"

#include "gui.h"

struct listOfSignals listOfSignals;
int pidRTL;

/*Bools of control*/
bool disasterMode;
bool sniperMode;
bool isRunning;

void newlistOfSignals() {
    listOfSignals.start = 0;
    listOfSignals.end = 0;
}

void startGUI() {
    isRunning = true;
    initGUI();
    //Launch UI
}

void sniperModeAttack(char *id, char *nameCar, char *temperature, char *pressure) {
    /*
    Si es toyota
        lanzo ataque toyota
    Si es citroen ataque citroen
    */
}

void enableSniperMode() {
    sniperMode = true;
}

void disableSniperMode() {
    sniperMode = false;
}

void enableDisasterMode() {
    disasterMode = true;
}

void disableDisasterMode() {
    disasterMode = false;
}

void turnOff() {
    isRunning = false;
}

void refreshView() {
    char temperature[20], pressure[20];
    SbListClear(List);
    for(int i = listOfSignals.start; i != listOfSignals.end; i++) {
        if(listOfSignals.tpmsSignals[i].time) {
            listOfSignals.start = (listOfSignals.start + 1) % MAX_SIGNALS ;
        }
        else {
            sprintf(temperature, "%f", listOfSignals.tpmsSignals[i].signal.temperature_C);
            sprintf(pressure, "%f", listOfSignals.tpmsSignals[i].signal.pressure_KPA);
            SbListInsert(List,
                            listOfSignals.tpmsSignals[i].signal.id,
                            listOfSignals.tpmsSignals[i].signal.model,
                            temperature,
                            pressure);
        }
    }
}

struct tpmsElement newTpmsElement(struct tpms_general str) {
    struct tpmsElement ret;
    ret.signal = str;
    ret.time = time(NULL);
    return ret;
}

int addSignal(const struct tpms_general signal) {
    if (signal.id == NULL)
        return -1;

    //Pointers of circular array
    listOfSignals.end = (listOfSignals.end + 1) % MAX_SIGNALS;
    listOfSignals.start += listOfSignals.start == listOfSignals.end;
    listOfSignals.start %= MAX_SIGNALS;

    listOfSignals.tpmsSignals[listOfSignals.end] = newTpmsElement(signal);

    return 1;
}

int launchRTL433() {
    int pidFork, fd_pipe[2];
    
    if(pipe(fd_pipe)) {
        perror("Pipe failed");
        return(-1);
    }

    pidFork = fork();
    if(pidFork == 0) {//child process
        char *args[] = {"sh", "-c", "rtl_433 -C si -F json", NULL};
        
        close(fd_pipe[READ_END]);
        dup2(fd_pipe[WRITE_END], STDOUT_FILENO);
        close(fd_pipe[WRITE_END]);

        if(execvp("/bin/sh", args) == -1){
            perror("Error when launching the program");
            return -1;
        }
    }
    else if(pidFork > 0){//parent process
        close(fd_pipe[WRITE_END]);
        pidRTL = pidFork;
        return fd_pipe[READ_END];
    }
    else{
        perror("fork creation failed\n");
        return -1;
    }    

    return 0;
}

void runController() {
    char buff[BUFFER_SIZE], *signal_buff;
    int fd_rtl;
    pthread_t gui_thread_id;
    //init array
    newlistOfSignals();
    isRunning = true;
    //init gui in a new thread
    pthread_create(&gui_thread_id, NULL, (void *)startGUI, NULL); 
    //startGUI();

    //initialize bools
    sniperMode = disasterMode = false;
    pidRTL = -1;

    while(isRunning) {//Run program
        while(sniperMode || disasterMode) {
            if(pidRTL == -1) { //Look if rtl is not running
                if((fd_rtl = launchRTL433()) == -1){ //Laucnh the rtl program
                    perror("");
                    sniperMode = disasterMode = false;
                    //launch error dialog
                    break;
                }
            }

            if(signal_buff == NULL) {
                signal_buff = malloc(1000);
                strcpy(signal_buff, "");
            }
            while (read(fd_rtl, buff, 1)){
                //Generate the string
                strcat(signal_buff, buff);

                if(buff[0] == '\n') {
                    //Parser string
                    struct tpms_general str = generalParser(signal_buff);
                    
                    if(disasterMode) {
                        //launch attack directly
                    }
                    else if(sniperMode){
                        addSignal(str);
                        refreshView();
                    }

                    free(signal_buff);
                    signal_buff = malloc(1000);
                    strcpy(signal_buff, "");
                }

            }
            refreshView();
        }

    }
}