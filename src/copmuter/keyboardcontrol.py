# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import serial
from pyfirmata import ArduinoMega
import keyboard

from motors import StepperMotor, ServoMotor

COM_PORT = 'COM5'
COM_BAUD = 9800

# Initialize motors
step_shoulder = StepperMotor()
step_base = StepperMotor()

serv_elbow = ServoMotor()
serv_wrist = ServoMotor()
serv_gripr = ServoMotor()


def main():
    ser = serial.Serial(COM_PORT, COM_BAUD, timeout=0)

    while True:
        event = keyboard.read_event()
        if event.name == 'esc':
            break

        if event.event_type == 'down':
            pass
        elif event.event_type == 'up':
            pass


if __name__ == '__main__':
    main()
