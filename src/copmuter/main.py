# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import cv2

import parameters as par
from kinematics import calculate_angle
from motors import RobotArm
from objectdetection import create_video_capture, detect_object


def main():
    cap = create_video_capture(par.CAM_NUM)
    arm = RobotArm(par.COM_PORT, par.COM_BAUD)

    while True:
        obj_x, obj_y = detect_object(cap)
        print(f'Object found at ({obj_x}, {obj_y})')
            
        key = cv2.waitKey(1)
        if key == ord('q'):
            break

        base_angle, shoulder_angle, elbow_angle, wrist_angle = calculate_angle(obj_x, obj_y, par.CAM_HEIGHT)
        arm.move_to_object(base_angle, shoulder_angle, elbow_angle, wrist_angle)
        arm.grab()
        arm.move_to_drop_off()
        arm.move_to_home()

    cap.release()
    

if __name__ == '__main__':
    main()