#!/bin/python3

#python library to transmit RF signals via CC1101 transceivers
#https://github.com/fphammerle/python-cc1101
import cc1101 
import sys #necessary for the arguments
import time
import logging
import binascii


def convertToByte(frame, lenPayload):
    return int(frame,2).to_bytes(lenPayload, 'big')

def configCC1101(transceiver):
    transceiver.set_base_frequency_hertz(433e6)
    transceiver._set_modulation_format(cc1101.ModulationFormat.FSK2)#Is a private method but we need FSK2 modulation
    transceiver.set_symbol_rate_baud(3900)
    transceiver.set_sync_mode(cc1101.SyncMode.NO_PREAMBLE_AND_SYNC_WORD)
    transceiver.disable_checksum()
    pass

def transmitC1101(transceiver, frame):
    for i in range(0,4):
        transceiver.transmit(frame)
        time.sleep(0.1)
    pass


if __name__ == "__main__":
    quit()
    logging.basicConfig(level=logging.INFO)
    lenPayload = len(sys.argv[1]) / 8
    lenPayload += lenPayload % 8 != 0
    lenPayload = int(lenPayload)
    print(lenPayload)
    convertToByte(sys.argv[1], lenPayload)
    quit()
    with cc1101.CC1101() as transceiver:
        configCC1101(transceiver)
        transmitC1101(transceiver, sys.argv[0].encode())#We need convert the frame to a bytes array
    pass

