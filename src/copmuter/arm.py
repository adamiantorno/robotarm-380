# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import serial
from enum import Enum

import parameters as par

class State(Enum):
    HOME = 1
    DROP = 2
    PICK = 3


class StepperMotor:
    def __init__(self, min_step, max_step) -> None:
        self.position = 0
        self.state = 0
        self.min = min_step
        self.max = max_step
    
    def angle_to_step(self, angle):
        return ((angle) / (180) * (self.max - self.min) + self.min)


class ServoMotor:
    def __init__(self, min_pos, max_pos) -> None:
        self.position = 0
        self.state = 0
        self.max = max_pos
        self.min = min_pos
    
    def angle_to_pos(self, angle):
        # in Degrees
        return ((angle) / (180) * (self.max - self.min) + self.min)


class RobotArm:
    def __init__(self, serial_port, serial_baud) -> None:
        self.state = State.HOME
        self.base = StepperMotor(par.BASE_MIN, par.BASE_MAX)
        self.shoulder = StepperMotor(par.SH_MIN, par.SH_MAX)
        self.elbow = ServoMotor(par.ELB_MIN, par.ELB_MAX)
        self.wrist = ServoMotor(par.WRIST_MIN, par.WRIST_MAX)
        self.gripper = ServoMotor(par.GRIP_MIN, par.GRIP_MAX)
        self.ser = serial.Serial(serial_port, serial_baud, timeout=0)

    def move_to(self, base_angle, shoulder_angle, elbow_angle, wrist_angle):
        self.base.position = self.base.angle_to_step(base_angle)
        self.shoulder.position = self.shoulder.angle_to_step(shoulder_angle)
        self.elbow.position = self.elbow.angle_to_pos(elbow_angle)
        self.wrist.position = self.wrist.angle_to_pos(wrist_angle)
        data = bytearray([])
        self.ser.write()
        

    def grab(self):
        self.gripper.position = self.gripper.angle_to_pos(par.GRIP_MAX)
        self.ser.write()
    
    def release(self):
        self.gripper.position = self.gripper.angle_to_pos(par.GRIP_MIN)
        self.ser.write()
        