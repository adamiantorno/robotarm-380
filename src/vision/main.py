# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import cv2


def show_webcam(mirror=False):
    cv = cv2.VideoCapture(0)
    while True:
        ret_val, img = cv.read()
        if mirror:
            img = cv2.flip(img, 1)
        cv2.imshow('webcam', img)
        if cv2.waitKey(1) == 27:
            break  # press escape to quit
    cv2.destroyAllWindows() 


def main():
    show_webcam(mirror=True)


if __name__ == '__main__':
    main()