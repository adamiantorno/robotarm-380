# Software Developped for ME 380 Project at the University of Waterloo - Group 7
# Paramters for Project
import numpy as np
import cv2

# Camera Config
CAM_NUM = 1

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
ORG_LOW = np.array([10, 100, 200])
ORG_UP = np.array([15, 255, 255])

#ORG_LOW = np.array([0, 120, 60])
#ORG_UP = np.array([10, 150, 80])

# Motor Config
BASE_MIN = -1000 # pick up
BASE_MAX = 1000  # drop off
BASE_HOME = 0
BASE_DROP = 700
BASE_CHG = 20
BASE_F = -880

SH_MIN = -1000 # back
SH_MAX = 3840 # forward
SH_HOME = 0
SH_DROP = 2500
SH_CHG = 128
SH_F = 3250

ELB_MIN = 200
ELB_MAX = 600
ELB_HOME = 325
ELB_DROP = 275
ELB_CHG = 5
ELB_F = 315

WRIST_MIN = 125
WRIST_MAX = 550
WRIST_HOME = 250
WRIST_DROP = 425
WRIST_CHG = 5
WRIST_F = 475

GRIP_MIN = 150
GRIP_MAX = 575
GRIP_HOME = 150
GRIP_DROP = GRIP_MIN
GRIP_CHG = 10
GRIP_F = 400

# base byte
BASE_BYTE = 0
SH_BYTE = 1
ELB_BYTE = 2
WRIST_BYTE = 3
GRIP_BYTE = 4
DIR_BYTE = 5



