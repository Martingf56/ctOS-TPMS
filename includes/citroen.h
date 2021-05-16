#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef CONVERTER_H
#define CONVERTER_H

#include "converter.h"

#endif

#ifndef ENCODERS_H
#define ENCODERS_H

#include "encoders.h"

#endif

#define PRESSURE_CONST 1.364 //Constant to divide the pression
#define TEMP_OFFSET 50 //The offset of the temperature

char* citroenTPMS(char* state, char *id, int flags, int repeat, float pressure, float temperature, int battery/*, char *filename*/);

