# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import serial
import numpy as np

import parameters as par

delimeter = b'\n'

increment_codes = {
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

class Motor:
    def __init__(self, min_pos, max_pos, chg, home, byte_index) -> None:
        self.min = min_pos
        self.max = max_pos
        self.chg = chg
        self.position = home
        self.byte_index = byte_index
        
    def pos_to_byte(self):
        old_range = self.max - self.min
        new_range = 255
        new_value = (((self.position - self.min) * new_range) / old_range)
        return int(new_value)

    def increment(self):
        self.position = min(self.position+self.chg, self.max)
        # ser_array = [0] * 6
        # ser_array[self.byte_index] = self.pos_to_byte()
        # ser_data = bytes(ser_array)
        # return ser_data
        return

    def decrement(self):
        self.position = max(self.position-self.chg, self.min)
        # ser_array = [0] * 6
        # ser_array[self.byte_index] = self.pos_to_byte()
        # ser_data = bytes(ser_array)
        # return ser_data
        return
    

class RobotArm:
    def __init__(self, serial_port, serial_baud) -> None:
        self.base = Motor(par.BASE_MIN, par.BASE_MAX, par.BASE_CHG, par.BASE_HOME, par.BASE_BYTE)
        self.shoulder = Motor(par.SH_MIN, par.SH_MAX, par.SH_CHG, par.SH_HOME, par.SH_BYTE)
        self.elbow = Motor(par.ELB_MIN, par.ELB_MAX, par.ELB_CHG, par.ELB_HOME, par.ELB_BYTE)
        self.wrist = Motor(par.WRIST_MIN, par.WRIST_MAX, par.WRIST_CHG, par.WRIST_HOME, par.WRIST_BYTE)
        self.gripper = Motor(par.GRIP_MIN, par.GRIP_MAX, par.GRIP_CHG, par.GRIP_HOME, par.GRIP_BYTE)
        self.ser = serial.Serial(serial_port, serial_baud, timeout=0)

    def move_to(self, base, shoulder, elbow, wrist, gripper, forward=True):
        self.base.position = base
        self.shoulder.position = shoulder
        self.elbow.position = elbow
        self.wrist.position = wrist
        self.gripper.position = gripper
        base_pos = self.base.pos_to_byte()
        sh_pos = self.shoulder.pos_to_byte()
        elb_pos = self.elbow.pos_to_byte()
        wrs_pos = self.wrist.pos_to_byte()
        grp_pos = self.gripper.pos_to_byte()
        direction = 0x00 if forward else 0x01
        data = bytes([base_pos, sh_pos, elb_pos, wrs_pos, grp_pos, direction, 0])
        self.ser.write(data + delimeter)

    def drop_off(self):
        self.move_to(par.BASE_DROP, par.SH_DROP, par.ELB_DROP, par.WRIST_DROP, par.GRIP_DROP, forward=False)
        # self.move_to(par.BASE_DROP, par.SH_F, par.ELB_F, par.WRIST_F, par.GRIP_DROP, forward=True)

    def home(self):
        self.move_to(par.BASE_HOME, par.SH_HOME, par.ELB_HOME, par.WRIST_HOME, par.GRIP_HOME, forward=False)

    def grab(self):
        self.gripper.position = par.GRIP_MIN
        b_pos = self.gripper.pos_to_byte()
        if b_pos == 0: b_pos = b_pos + 1
        data = bytes([0, 0, 0, 0, b_pos, 0, 0])
        self.ser.write(data + delimeter)
    
    def release(self):
        self.gripper.position = par.GRIP_MAX
        b_pos = self.gripper.pos_to_byte()
        data = bytes([0, 0, 0, 0, b_pos, 0, 0])
        self.ser.write(data + delimeter)
    
    def increment_motor(self, motor, d):
        motor.increment()
        ser_array = [0] * 7
        ser_array[6] = ord(increment_codes[d])
        print(ser_array)
        data = bytes(ser_array)
        # self.ser.write(increment_codes[d])
        self.ser.write(data + delimeter)
        return

    def decrement_motor(self, motor, d):
        motor.decrement()
        ser_array = [0] * 7
        ser_array[6] = ord(increment_codes[d])
        print(ser_array)
        data = bytes(ser_array)
        # self.ser.write(increment_codes[d])
        self.ser.write(data + delimeter)
        return

    def read(self):
        d = self.ser.readline()
        print(d)
    