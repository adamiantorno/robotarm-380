# Software Developped for ME 380 Project at the University of Waterloo - Group 7
# Paramters for Project
import numpy as np

# Camera Config
CAM_NUM = 0

# Arduino Config
COM_PORT = 'COM5'
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
BASE_MIN = 0
BASE_MAX = 100
BASE_HOME = 50
BASE_DROP = 50

SH_MIN = 0
SH_MAX = 100
SH_HOME = 50
SH_DROP = 50

ELB_MIN = 0
ELB_MAX = 100
ELB_HOME = 50
ELB_DROP = 50

WRIST_MIN = 0
WRIST_MAX = 100
WRIST_HOME = 50
WRIST_DROP = 50

GRIP_MIN = 0
GRIP_MAX = 100
GRIP_HOME = 50
GRIP_HOME = 50

