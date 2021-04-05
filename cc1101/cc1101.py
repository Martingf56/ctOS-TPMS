#!/bin/python3

#python library to transmit RF signals via CC1101 transceivers
#https://github.com/fphammerle/python-cc1101
import cc1101 
import sys #necessary for the arguments
from bitarray import bitarray


def convertToByte(frame):
    #array_byte = []
    #for byte in range(0, 200, 8):
    #    print(frame[byte:(byte + 8)])
    #    array_byte.append(int(frame[byte:byte+8], 2))

    print(frame)
    print(int(frame, 2))
    return int(frame, 2).to_bytes(25, 'big')

def configCC1101(transceiver):
    transceiver.set_base_frequency_hertz(433e6)
    transceiver._set_modulation_format(cc1101.ModulationFormat.FSK2)#Is a private method but we need FSK2 modulation
    transceiver.set_symbol_rate_baud(3900)
    transceiver.set_sync_mode(cc1101.SyncMode.NO_PREAMBLE_AND_SYNC_WORD)
    transceiver.disable_checksum()
    pass

def transmitC1101(transceiver, frame):
    transceiver.transmit(frame)
    pass


if __name__ == "__main__":
    #print(convertToByte("01010101010101010101010101010110101010011010010101101010011001101001100101101010010101010110100101100110101001101010101010101001011001011010011010011010101010011010010101101010100101100110101001111110"))
    print(convertToByte(sys.argv[1]))
    quit()
    with cc1101.CC1101() as transceiver:
        configCC1101(transceiver)
        #print("modulation format", transceiver.get_modulation_format().name)
        transmitC1101(transceiver, sys.argv[0].encode())#We need convert the frame to a bytes array
    
    pass

