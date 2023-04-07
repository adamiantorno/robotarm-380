# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import cv2
from collections import deque

import parameters as par
from kinematics import calculate_angle
from arm import RobotArm
from objectdetection import create_video_capture, detect_object


def add_to_objects(deq, coords):
    for item in deq:
        if len(item) == len(coords) and (abs(item[0] - coords[0]) < 2) and (abs(item[0] - coords[0]) < 2):
            return
    deque.append(coords)
    return
    

def main():
    cap = create_video_capture(par.CAM_NUM)
    object_queue = deque()
    # arm = RobotArm(par.COM_PORT, par.COM_BAUD)

    while True:
        obj_x, obj_y = detect_object(cap)
        print(f'Object found at ({obj_x}, {obj_y})')
        if cv2.waitKey(1) == ord('q'):
            break

        # Chedck if object is in deque already
        add_to_objects(object_queue, (obj_x, obj_y))

        # base_angle, shoulder_angle, elbow_angle, wrist_angle = calculate_angle(obj_x, obj_y)
        # arm.move_to(base_angle, shoulder_angle, elbow_angle, wrist_angle)
        # arm.grab()
        # arm.move_to(par.BASE_DROP, par.SH_DROP, par.ELB_DROP, par.WRIST_DROP)
        # arm.release()
        # arm.move_to(par.BASE_HOME, par.SH_HOME, par.ELB_HOME, par.WRIST_HOME)


    cap.release()
    

if __name__ == '__main__':
    main()