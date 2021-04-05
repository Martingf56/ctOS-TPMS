#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>




#ifndef TPMS_STRUCT
#define TPMS_STRUCT
#include "tpms_structs.h"
#endif

//Include cars
#include "toyota.h"
#include "citroen.h"

#define PIPE_BUFF_SIZE 200

bool transmitTPMSSignal(struct tpms_general tpms);