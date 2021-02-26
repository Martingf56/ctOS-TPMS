#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h> //Only for compilers with the pthread librarie
#include <unistd.h>


#ifndef TPMS_STRUCT
#define TPMS_STRUCT
#include "tpms_structs.h"
#endif

#define MAX_SIGNALS 15
#define MAX_TIME 30 //Max time for use a tpms signal
#define BUFFER_SIZE 1 //For read rtl
#define PIPE 2 //PIPE
#define READ_END 0  //PIPE
#define WRITE_END 1 //PIPE


struct tpmsElement {
   struct tpms_general signal;//Contiene informacion
   time_t time; //Para saber cuanto lleva
};

struct listOfSignals {
    struct tpmsElement tpmsSignals[MAX_SIGNALS]; //El array que se mostrará en la lista
    int start;
    int end;
    int size;
};

void newlistOfSignals();

void startGUI();

void sniperModeAttack(char *id, char *nameCar, char *temperature, char *pressure);

void enableSniperMode();
void disableSniperMode() ;
bool getSniperMode();
void enableDisasterMode();
void disableDisasterMode();
bool getDisasterMode();
void killRTL433();
void turnOff();

void refreshView();

struct tpmsElement newTpmsElement(struct tpms_general str);

int addSignal(const struct tpms_general signal);

int launchRTL433();

void runController();

