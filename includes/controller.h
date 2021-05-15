#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h> //Only for compilers with the pthread librarie
#include <unistd.h>


#ifndef TPMS_STRUCT
#define TPMS_STRUCT
#include "tpms_structs.h"
#endif

#include "transmiter.h"
#include "gui.h"

#define MAX_SIGNALS 15
#define MAX_TIME 30 //Max time for use a tpms signal
#define BUFFER_SIZE 1 //For read rtl
#define PIPE 2 //PIPE
#define READ_END 0  //PIPE
#define WRITE_END 1 //PIPE


struct tpmsElement {
   struct tpms_general signal;//Contain the tpms information
   time_t time; //Time for measure the duration on the list
};

struct listOfSignals {
    struct tpmsElement tpmsSignals[MAX_SIGNALS]; //Array of tpms signals
    //Pointer of circular array
    int start;
    int end;
    int size;
};

//Initialize the pointer of the circular array
void newlistOfSignals();

//Funcntion to call for init the GUI
void startGUI();

//Launch a tpms attack and return if was possible to launch
bool launchAttack(struct tpms_general tpms);

//Function for attack a single car, need the id of the wheel and the model of the vehicle
void sniperModeAttack(char *id, char *nameCar);

void enableSniperMode();
void disableSniperMode() ;
bool getSniperMode();
void enableDisasterMode();
void disableDisasterMode();
bool getDisasterMode();

//Kill the rtl 433 and not search more topms signals
void killRTL433();

//Quit the app
void turnOff();

//Refresh the view of the tpms list on the GUI
void refreshView(const char *list);

struct tpmsElement newTpmsElement(struct tpms_general str);

//Add signal to th circular array
int addSignal(const struct tpms_general signal);

//Start the rtl 433 on a different process
int launchRTL433();

//Principal function of the controller, is the main program
void runController();

