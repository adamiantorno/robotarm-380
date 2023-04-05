# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import serial
import keyboard
import time

COM_PORT = 'COM7'
COM_BAUD = 9800

key_code_map = {
    17: b'W',
    31: b'S',
    18: b'E',
    32: b'D',
    19: b'R',
    33: b'F',
    20: b'T',
    34: b'G',
    21: b'Y',
    35: b'H'
}

def main():
    ser = serial.Serial(COM_PORT, COM_BAUD, timeout=0)
    time.sleep(1)
    print('Ready to send serial data')
    
    while True:  
        event = keyboard.read_event()
        if event.name == 'esc':
            break
        try:
            print(key_code_map[event.scan_code])
            ser.write(key_code_map[event.scan_code])
        except KeyError:
            print('Not a valid motor control')
    ser.close()


if __name__ == '__main__':
    main()
