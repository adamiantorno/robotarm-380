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

        base_angle, shoulder_angle, elbow_angle, wrist_angle = calculate_angle(obj_x, obj_y)
        arm.move_to(base_angle, shoulder_angle, elbow_angle, wrist_angle)
        arm.grab()
        arm.move_to(par.BASE_DROP, par.SH_DROP, par.ELB_DROP, par.WRIST_DROP)
        arm.release()
        arm.move_to(par.BASE_HOME, par.SH_HOME, par.ELB_HOME, par.WRIST_HOME)


    cap.release()
    

if __name__ == '__main__':
    main()