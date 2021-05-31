#!/bin/bash

FILE_IN="./datagram.txt"
FILE_OUT="./datagram.cu8"
ROUTE_TX_TOOLS="../"

####CREATE FILE
FIXED_PARAMS="[_(8000us)]\n[-(150us)]\n[0(-40kHz52us)]\n[1(40kHz52us)]\n_ _\n"
spoof_datagram=$1
echo -e $FIXED_PARAMS$spoof_datagram > $FILE_IN
cat $FILE_IN
####

###Convert the file to tx_tools
${ROUTE_TX_TOOLS}tx_tools/build/code_gen -s 250k -r $FILE_IN -w $FILE_OUT
####

###Launch RTL_433
rtl_433 -r $FILE_OUT -F json
####

rm $FILE_IN $FILE_OUT
