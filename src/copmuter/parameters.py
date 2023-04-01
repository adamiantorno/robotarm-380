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
SHOULDER_LENGTH = 2
ELBOW_LENGTH = 1

# Object Detection HSV COLOR Ranges
# Orange
ORG_LOW = np.array([0, 100, 100])
ORG_UP = np.array([20, 255, 255])


