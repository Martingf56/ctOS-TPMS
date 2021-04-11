#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

//Receive a decimal int and convert them to a string of his bits with the len size
char* dec2bin(long int c, int len);

//Do a xor logic operation between two strings 
char* xor(char *check, char* next8bits);