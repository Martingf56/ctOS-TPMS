#!/bin/python3

#python library to transmit RF signals via CC1101 transceivers
#https://github.com/fphammerle/python-cc1101
import cc1101 
import sys #necessary for the arguments

def configCC1101(transceiver):
    transceiver.set_base_frequency_hertz(433e6)
    transceiver._set_modulation_format(0b000)#Is a private method but we need FSK2 modulation
    transceiver.set_symbol_rate_baud(600)
    transceiver.set_sync_mode(cc1101.SyncMode.NO_PREAMBLE_AND_SYNC_WORD)
    transceiver.disable_checksum()
    pass

def transmitC1101(transceiver, frame):
    transceiver.transmit(frame)
    pass


if __name__ == "__main__":
    
    with cc1101.CC1101() as transceiver:
        configCC1101(transceiver)
        transmitC1101(transceiver, sys.argv[0])
    
    pass
