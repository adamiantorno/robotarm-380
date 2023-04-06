
import keyboard

from kinematics import calculate_angle
from arm import RobotArm
import parameters as par

def main():
    arm = RobotArm(par.COM_PORT, par.COM_BAUD)

    while True:
        event = keyboard.read_event()
        if event.name == 'esc':
            break
            
        if event.name == 'q' and event.event_type == 'down':
            # grab
            pass
        elif event.name == 'w' and event.event_type == 'down':
            # release
            pass
        elif event.name == 'e' and event.event_type == 'down':
            # home position
            pass
        elif event.name == 'r' and event.event_type == 'down':
            # drop off position
            pass
            

            print('hello')



if __name__ == '__main__':
    main()