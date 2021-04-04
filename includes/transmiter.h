#include <sys/types.h>
#include <unistd.h>


#ifndef TPMS_STRUCT
#define TPMS_STRUCT
#include "tpms_structs.h"
#endif

//Include cars
#include "toyota.h"
#include "citroen.h"

bool transmitTPMSSignal(struct tpms_general tpms);