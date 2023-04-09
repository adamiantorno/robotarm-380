# Software Developped for ME 380 Project at the University of Waterloo - Group 7
# Paramters for Project
import numpy as np

# Camera Config
CAM_NUM = 0

# Arduino Config
COM_PORT = 'COM7'
COM_BAUD = 9800

# Arm Config (Dimmension in mm)
CAM_HEIGHT = 4
BASE_HEIGHT = 1
SH_L = 2
ELB_L = 1

# Object Detection HSV COLOR Ranges
# Orange
ORG_LOW = np.array([0, 100, 100])
ORG_UP = np.array([20, 255, 255])

# Motor Config
BASE_MIN = -1000 # pick up
BASE_MAX = 1000  # drop off
BASE_HOME = 0
BASE_DROP = 500
BASE_CHG = 20

SH_MIN = -1000 # back
SH_MAX = 3840 # forward
SH_HOME = 0
SH_DROP = 2000
SH_CHG = 128

ELB_MIN = 200
ELB_MAX = 600
ELB_HOME = 325
ELB_DROP = 250
ELB_CHG = 5

WRIST_MIN = 125
WRIST_MAX = 550
WRIST_HOME = 250
WRIST_DROP = 500
WRIST_CHG = 5

GRIP_MIN = 150
GRIP_MAX = 575
GRIP_HOME = 150
GRIP_DROP = GRIP_MIN
GRIP_CHG = 10

# base byte
BASE_BYTE = 0
SH_BYTE = 1
ELB_BYTE = 2
WRIST_BYTE = 3
GRIP_BYTE = 4
DIR_BYTE = 5



