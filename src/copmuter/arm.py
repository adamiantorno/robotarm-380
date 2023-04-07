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

    def pos_to_byte(self, value, min_pos, max_pos):
        old_range = max_pos - min_pos
        new_range = 255
        new_value = (((value - min_pos) * new_range) / old_range)
        # return bin(int(new_value))[2:].zfill(8)
        return int(new_value)

    def move_to(self, base_angle, shoulder_angle, elbow_angle, wrist_angle):
        self.base.position = self.base.angle_to_step(base_angle)
        self.shoulder.position = self.shoulder.angle_to_step(shoulder_angle)
        self.elbow.position = self.elbow.angle_to_pos(elbow_angle)
        self.wrist.position = self.wrist.angle_to_pos(wrist_angle)
        data = bytearray([])
        self.ser.write()

    def move_to_home(self):
        # need to add stepper
        self.elbow.position = par.ELB_HOME
        self.wrist.position = par.WRIST_HOME
        self.gripper.position = par.GRIP_HOME
        elb_pos = self.pos_to_byte(self.elbow.position, par.ELB_MIN, par.ELB_MAX)
        wrs_pos = self.pos_to_byte(self.wrist.position, par.WRIST_MIN, par.WRIST_MAX)
        grp_pos = self.pos_to_byte(self.gripper.position, par.GRIP_MIN, par.GRIP_MAX)
        data = bytes([0, 0, elb_pos, wrs_pos, grp_pos])
        self.ser.write(data)

    def move_to_dropoff(self):
        # need to add stepper
        self.elbow.position = par.ELB_DROP
        self.wrist.position = par.WRIST_DROP
        self.gripper.position = par.GRIP_DROP
        elb_pos = self.pos_to_byte(self.elbow.position, par.ELB_MIN, par.ELB_MAX)
        wrs_pos = self.pos_to_byte(self.wrist.position, par.WRIST_MIN, par.WRIST_MAX)
        grp_pos = self.pos_to_byte(self.gripper.position, par.GRIP_MIN, par.GRIP_MAX)
        data = bytes([0, 0, elb_pos, wrs_pos, grp_pos])
        self.ser.write(data) 

    def grab(self):
        self.gripper.position = par.GRIP_MIN
        b_pos = self.pos_to_byte(self.gripper.position, par.GRIP_MIN, par.GRIP_MAX)
        if b_pos == 0: b_pos = b_pos + 1
        data = bytes([0, 0, 0, 0, b_pos])
        delimeter = b'\n'
        self.ser.write(data + delimeter)
    
    def release(self):
        self.gripper.position = par.GRIP_MAX
        b_pos = self.pos_to_byte(self.gripper.position, par.GRIP_MIN, par.GRIP_MAX)
        data = bytes([0, 0, 0, 0, b_pos])
        delimeter = b'\n'
        self.ser.write(data + delimeter)
    
    def read(self):
        d = self.ser.readline()
        print(d)
    