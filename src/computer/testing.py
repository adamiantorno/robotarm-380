
import keyboard

from kinematics import calculate_angle
from arm import RobotArm
import parameters as par

def main():
    arm = RobotArm(par.COM_PORT, par.COM_BAUD)

    while True:
        event = keyboard.read_event()
        if event.name == 'esc': # close programw
            break
        if event.name == 'q' and event.event_type == 'down': # grab
            print('grab')
            arm.grab()
        elif event.name == 'w' and event.event_type == 'down': # release
            print('release')
            arm.release()
        elif event.name == 'e' and event.event_type == 'down': # home position
            print('home')
            arm.move_to_home()
        elif event.name == 'r' and event.event_type == 'down': # drop off position
            print('drop')
            arm.move_to_dropoff()
        
        arm.read()
        

if __name__ == '__main__':
    main()