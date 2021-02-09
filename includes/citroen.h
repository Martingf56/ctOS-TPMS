#include <string.h>
#include <stdlib.h>

#ifndef CONVERTER_H
#define CONVERTER_H

#include "converter.h"

#endif

#ifndef ENCODERS_H
#define ENCODERS_H

#include "encoders.h"

#endif

#define PRESSURE_CONST 1.364 /*Constante por la que dividimos la presion*/

#define TEMP_OFFSET 50 /*Desplazamiento de la temperatura*/

void citroenTPMS(char* state, char *id, int flags, int repeat, float pressure, float temperature, int battery/*, char *filename*/);

