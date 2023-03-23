# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import cv2
import numpy as np


# Define HSV COLOR Ranges
#Orange
ORG_LOW = np.array([0, 100, 100])
ORG_UP = np.array([20, 255, 255])


def obj_center(box):
    M = cv2.moments(box)
    center_x = int(M['m10'] / M['m00'])
    center_y = int(M['m01'] / M['m00'])
    return [center_x, center_y]


def create_video_capture(device_id):
    cap = cv2.VideoCapture(device_id)
    if not cap.isOpened():
        raise Exception("Could not open video device")
    return cap


def detect_object(cap):
    ret, frame = cap.read()
    imgBlur = cv2.GaussianBlur(frame, (7, 7), 3)
    hsv = cv2.cvtColor(imgBlur, cv2.COLOR_BGR2HSV)
    
    # detect orange in feed
    orange_mask = cv2.inRange(hsv, ORG_LOW, ORG_UP)
    contours, _ = cv2.findContours(orange_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # find contour with the largest area
    max_area = 0
    max_contour = None
    for contour in contours:
        area = cv2.contourArea(contour)
        if area > max_area:
            max_area = area
            max_contour = contour
        
        if max_contour is not None:
            obj_x = obj_center(max_contour)[0]
            obj_y = obj_center(max_contour)[1]

            # cv2.circle(frame, (obj_x, obj_y), 10, (0, 255, 0), 2)

            height, width, _ = frame.shape
            x = obj_x - (width / 2)
            y = (height / 2) - obj_y

         # cv2.imshow('orange detection', frame)    
    return x, y
