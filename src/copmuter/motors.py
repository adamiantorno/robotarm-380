# Software Developped for ME 380 Project at the University of Waterloo - Group 7

class StepperMotor:
    def __init__(self) -> None:
        self.position = 0
        self.state = 0


class ServoMotor:
    def __init__(self) -> None:
        self.position = 0
        self.state = 0


class RobotArm:
    def __init__(self) -> None:
        self.state()
        self.base = StepperMotor()
        self.shoulder = StepperMotor()
        self.elbow = ServoMotor()
        self.wrist = ServoMotor()
        self.gripper = ServoMotor()

    def move_to_obj(base_angle, shoulder_angle, elbow_angle, wrist_angle):
        pass

    def grab():
        pass

    def move_to_drop_off():
        pass

    def move_to_home():
        pass