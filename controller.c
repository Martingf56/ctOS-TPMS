#include "includes/controller.h"
#include <signal.h>



struct listOfSignals listOfSignals;
struct listOfSignals listOfSignals_AA;
int pidRTL;

/*Bools of control*/
bool disasterMode;
bool sniperMode;
bool isRunning;

void newlistOfSignals() {
    listOfSignals.start = -1;
    listOfSignals.end = -1;
    listOfSignals.size = 0;

    listOfSignals_AA.start = -1;
    listOfSignals_AA.end = -1;
    listOfSignals_AA.size = 0;
}

void startGUI() {
    isRunning = true;
    initGUI();
    //Launch UI
}

bool launchAttack(struct tpms_general tpms) {
    if (!strncmp(tpms.model, "Toyota", strlen("Toyota")))
        toyotaTPMS(tpms.status, tpms.id, tpms.pressure_KPA, tpms.temperature_C);
    else if (!strncmp(tpms.model, "Citroen", strlen("Citroen"))) 
        citroenTPMS(tpms.state, tpms.id, tpms.flags, tpms.repeat, tpms.pressure_KPA, tpms.temperature_C, tpms.maybe_battery);
    else if (!strncmp(tpms.model, "Renault", strlen("Renault"))) 
        renaultTPMS(tpms.id, tpms.pressure_KPA, tpms.temperature_C, tpms.flags);
    
    return NULL;
    //return transmitTPMSSignal(tpms);
}

void sniperModeAttack(char *id, char *nameCar) {
    struct tpms_general tpms = newFakeSignal(id, nameCar);
    
    
    launchAttack(tpms);//if bad display problems on the transmit
}

void enableSniperMode() {
    sniperMode = true;
}

void disableSniperMode() {
    sniperMode = false;
}

bool getSniperMode() {
    return sniperMode;
}

void enableDisasterMode() {
    disasterMode = true;
}

void disableDisasterMode() {
    disasterMode = false;
}

bool getDisasterMode() {
    return disasterMode;
}

void killRTL433() {
    if(pidRTL == -1) //IMPORTANT
        return;
    //Send signal to process group of child
    kill((-1*pidRTL), SIGTERM);
    pidRTL = -1;
} 

void turnOff() {
    isRunning = false;
    killRTL433();
}

void refreshView(const char *list) {
    char temperature[20], pressure[20];

    //Clear the list of vehicles
    
    if (!strncmp(list, "AO", strlen("AO"))){
        SbListClear(List_AO);
        int pos = listOfSignals.start;
        for(int i = 0; i < listOfSignals.size; i++){
            if(difftime(time(NULL), listOfSignals.tpmsSignals[pos].time) >= MAX_TIME) {
                listOfSignals.start = (listOfSignals.start + 1) % MAX_SIGNALS;
                listOfSignals.size--;
            }
            else {
                sprintf(temperature, "%f", listOfSignals.tpmsSignals[pos].signal.temperature_C);
                sprintf(pressure, "%f", listOfSignals.tpmsSignals[pos].signal.pressure_KPA);
                SbListInsert(List_AO,
                                listOfSignals.tpmsSignals[pos].signal.id,
                                listOfSignals.tpmsSignals[pos].signal.model,
                                temperature,
                                pressure);
            }
        pos = (pos+1) % MAX_SIGNALS;
        }
    }
    else if(!strncmp(list, "AA", strlen("AA"))){
        SbListClear(List_AA);
        for(int i = 0; i < listOfSignals_AA.size; i++){
            sprintf(temperature, "%f", listOfSignals_AA.tpmsSignals[i].signal.temperature_C);
            sprintf(pressure, "%f", listOfSignals_AA.tpmsSignals[i].signal.pressure_KPA);
            SbListInsert(List_AA,
                            listOfSignals_AA.tpmsSignals[i].signal.id,
                            listOfSignals_AA.tpmsSignals[i].signal.model,
                            temperature,
                            pressure);
        
        }
    }
   /* gtk_entry_set_text(GTK_ENTRY(EntryID), "");
    gtk_combo_box_set_active_id (GTK_COMBO_BOX(ComboboxModel), NULL);*/
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

    listOfSignals.tpmsSignals[listOfSignals.end] = newTpmsElement(signal);
    listOfSignals.size++;
    if(listOfSignals.size > MAX_SIGNALS)
        listOfSignals.size = MAX_SIGNALS;
    
    listOfSignals.start += listOfSignals.start == listOfSignals.end;
    if(listOfSignals.start == -1)
        listOfSignals.start = 0;
    listOfSignals.start %= MAX_SIGNALS;

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
        char *args[] = {"sh", "-c", "rtl_433 -C si -F json -R 82 -R 88", NULL};
        
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
        //Make child process the leader of its own process group. This allows signals to also be delivered to processes forked by the child process.
        setpgid(pidRTL, 0);
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
    /*
    addSignal(generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"13\", \"id\" : \"8a58f9a2\", \"flags\" : 0, \"repeat\" : 1, \"pressure_kPa\" : 242.792, \"temperature_C\" : 15.000, \"maybe_battery\" : 56, \"mic\" : \"CHECKSUM\"}"));
    addSignal(generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"fb26ac5a\",\"status\" : 131,\"pressure_kPa\" : 253.382,\"temperature_C\" : 14.000,\"mic\" : \"CRC\"}"));
    addSignal(generalParser("{\"time\" : \"2020-12-04 13:04:21\", \"model\" : \"Citroen\", \"type\" : \"TPMS\", \"state\" : \"13\", \"id\" : \"8a58f9a3\", \"flags\" : 0, \"repeat\" : 1, \"pressure_kPa\" : 215.662, \"temperature_C\" : 11.000, \"maybe_battery\" : 56, \"mic\" : \"CHECKSUM\"}"));
    addSignal(generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"fb26ac5b\",\"status\" : 131,\"pressure_kPa\" : 280.777,\"temperature_C\" : 20.000,\"mic\" : \"CRC\"}"));
    addSignal(generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"fb26ac5c\",\"status\" : 131,\"pressure_kPa\" : 266.666,\"temperature_C\" : 17.000,\"mic\" : \"CRC\"}"));
    */
    
    //init gui in a new thread
    pthread_create(&gui_thread_id, NULL, (void *)startGUI, NULL); 
    //startGUI();

   // addSignal(generalParser("{\"time\" : \"2020-12-04 13:09:17\",\"model\" : \"Toyota\",\"type\" : \"TPMS\",\"id\" : \"fb26ac5a\",\"status\" : 131,\"pressure_kPa\" : 253.382,\"temperature_C\" : 14.000,\"mic\" : \"CRC\"}"));

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

            if(signal_buff) {
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
                        launchAttack(str);
                        addSignal(str);
                    }
                    else if(sniperMode){
                        addSignal(str);
                    }

                    free(signal_buff);
                    signal_buff = malloc(1000);
                    strcpy(signal_buff, "");
                }

            }
        }
    }
}