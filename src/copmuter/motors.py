# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import serial

class StepperMotor:
    def __init__(self) -> None:
        self.position = 0
        self.state = 0


class ServoMotor:
    def __init__(self) -> None:
        self.position = 0
        self.state = 0


class RobotArm:
    def __init__(self, serial_port, serial_baud) -> None:
        self.state()
        self.base = StepperMotor()
        self.shoulder = StepperMotor()
        self.elbow = ServoMotor()
        self.wrist = ServoMotor()
        self.gripper = ServoMotor()
        self.ser = serial.Serial(serial_port, serial_baud, timeout=0)

    def move_to_obj(self, base_angle, shoulder_angle, elbow_angle, wrist_angle):
        self.base.position = base_angle
        self.shoulder.position = shoulder_angle
        self.elbow.position = elbow_angle
        self.wrist.position = wrist_angle
        

    def grab():
        pass

    def move_to_drop_off():
        pass

    def move_to_home():
        pass