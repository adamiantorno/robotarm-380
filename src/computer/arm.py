# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import serial
from enum import Enum

import parameters as par

delimeter = b'\n'


class StepperMotor:
    def __init__(self, home, min_step, max_step, chg, byte_index) -> None:
        self.position = home
        self.byte_index = byte_index
        self.chg = chg
        self.min = min_step
        self.max = max_step
    
    def pos_to_byte(self):
        pass

    def increment(self):
        self.position = min(self.position+self.chg, self.max_step)
        data = bytes([0, 0, 0, 0, 0])

    def decrement(self):
        pass
    
    # def angle_to_step(self, angle):
    #     return ((angle) / (180) * (self.max - self.min) + self.min)


class ServoMotor:
    def __init__(self, home, min_pos, max_pos, chg, byte_index) -> None:
        self.position = home
        self.byte_index = byte_index
        self.chg = chg
        self.max = max_pos
        self.min = min_pos
    
    def pos_to_byte(self):
        pass

    def increment(self):
        pass

    def decrement(self):
        pass


    
    # def angle_to_pos(self, angle):
    #     # in Degrees
    #     return ((angle) / (180) * (self.max - self.min) + self.min)
    

class RobotArm:
    def __init__(self, serial_port, serial_baud) -> None:
        self.base = StepperMotor(par.BASE_HOME, par.BASE_MIN, par.BASE_MAX, par.BASE_CHG, par.BASE_BYTE)
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

    # def move_to(self, base_angle, shoulder_angle, elbow_angle, wrist_angle):
    #     self.base.position = self.base.angle_to_step(base_angle)
    #     self.shoulder.position = self.shoulder.angle_to_step(shoulder_angle)
    #     self.elbow.position = self.elbow.angle_to_pos(elbow_angle)
    #     self.wrist.position = self.wrist.angle_to_pos(wrist_angle)
    #     data = bytearray([])
    #     self.ser.write()

    def move_to(self, base, shoulder, elbow, wrist, gripper, forward=True):
        self.base.position = base
        self.shoulder.position = shoulder
        self.elbow.position = elbow
        self.wrist.position = wrist
        self.gripper.position = gripper
        base_pos = self.pos_to_byte(self.base.position, par.BASE_MIN, par.BASE_MAX)
        sh_pos = self.pos_to_byte(self.shoulder.position, par.SH_MIN, par.SH_MAX)
        elb_pos = self.pos_to_byte(self.elbow.position, par.ELB_MIN, par.ELB_MAX)
        wrs_pos = self.pos_to_byte(self.wrist.position, par.WRIST_MIN, par.WRIST_MAX)
        grp_pos = self.pos_to_byte(self.gripper.position, par.GRIP_MIN, par.GRIP_MAX)
        direction = 0x01 if forward else 0x02
        data = bytes([base_pos, sh_pos, elb_pos, wrs_pos, grp_pos, direction])
        self.ser.write(data + delimeter)

    def grab(self):
        self.gripper.position = par.GRIP_MIN
        b_pos = self.pos_to_byte(self.gripper.position, par.GRIP_MIN, par.GRIP_MAX)
        if b_pos == 0: b_pos = b_pos + 1
        data = bytes([0, 0, 0, 0, b_pos])
        self.ser.write(data + delimeter)
    
    def release(self):
        self.gripper.position = par.GRIP_MAX
        b_pos = self.pos_to_byte(self.gripper.position, par.GRIP_MIN, par.GRIP_MAX)
        data = bytes([0, 0, 0, 0, b_pos])
        self.ser.write(data + delimeter)
    

    def read(self):
        d = self.ser.readline()
        print(d)
    