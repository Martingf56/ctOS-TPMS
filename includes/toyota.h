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

#define PRESSURE_CONSTANT 4
#define PRESSURE_OFFSET 7
#define TEMPERATURE_OFFSET 40


void toyotaTPMS(char *status, char *id, float pressure, float temperature);
