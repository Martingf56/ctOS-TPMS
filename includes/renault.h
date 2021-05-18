#include <stdio.h>
#include <string.h>

#ifndef CONVERTER_H
#define CONVERTER_H

#include "converter.h"

#endif
#ifndef ENCODERS_H
#define ENCODERS_H

#include "encoders.h"

#endif
#include "crc.h"

#define PRESSURE_CONSTANT_RENAULT 0.75
#define TEMPERATURE_OFFSET_RENAULT 30

//Collect the params and create a renault TPMS signal
char* renaultTPMS(char *id, float pressure, float temperature, int flags);