# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import keyboard
import serial
import time, sys

COM_PORT = 'COM5'
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
    ser = serial.Serial(COM_PORT, 9800, timeout=1)

    while True:
        event = keyboard.read_event()
        if event.name == 'esc':
            break

        if event.event_type == 'down':
            print(f'sent {event.scan_code}')
            try:
                ser.write(key_code_map[event.scan_code])
            except KeyError:
                print('Not a valid motor control')
        elif event.event_type == 'up':
            print('up key')
            try:
                ser.write(b'P')
            except KeyError:
                print('ERROR in comm w/ Arduino')
 
    

if __name__ == '__main__':
    main()