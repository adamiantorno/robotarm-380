# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import cv2
import numpy as np

CAM_NUM = 0

# Define HSV COLOR Ranges
#Orange
ORG_LOW = np.array([0, 100, 100])
ORG_UP = np.array([20, 255, 255])

cap = cv2.VideoCapture(CAM_NUM)

def obj_center(box):
    M = cv2.moments(box)
    center_x = int(M['m10'] / M['m00'])
    center_y = int(M['m01'] / M['m00'])
    return [center_x, center_y]

def main():
    while True:
        ret, frame = cap.read()
        imgBlur = cv2.GaussianBlur(frame, (7, 7), 3)
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

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

            cv2.circle(frame, (obj_x, obj_y), 10, (0, 255, 0), 2)

            height, width, _ = frame.shape
            x = obj_x - (width / 2)
            y = (height / 2) - obj_y
            print(f'Object found at ({x}, {y})')

        # draw contours
        # cv2.drawContours(frame, contours, -1, (0, 255, 0), 3)
        cv2.imshow('orange detection', frame)

        # wait for user to press a key
        key = cv2.waitKey(1)
        if key == ord('q'):
            break




if __name__ == '__main__':
    main()
    cap.release()
    cv2.destroyAllWindows()
    