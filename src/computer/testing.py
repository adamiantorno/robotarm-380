
import keyboard
import time

from kinematics import calculate_angle
from arm import RobotArm
import parameters as par

def main():
    arm = RobotArm(par.COM_PORT, par.COM_BAUD)
    time.sleep(1)
    print('Ready to send serial data')

    while True:
        event = keyboard.read_event()
        if event.name == 'esc': # close programw
            break

        if event.name == 'u' and event.event_type == 'down': # fake pickup
            print('fake pickup')
            arm.move_to(par.BASE_F, par.SH_F, par.ELB_F, par.WRIST_F, par.GRIP_F, forward=True)
            arm.grab()
            arm.drop_off()
            arm.release()
            # arm.grab()
            arm.home()
            arm.grab()
        elif event.name == 'p' and event.event_type == 'down': # automatedpickup
            print('pick up')
            arm.move_to()

        elif event.name =='o' and event.event_type == 'down': # dropoff
            print('dropoff')
            arm.drop_off()

        elif event.name == 'i' and event.event_type == 'down': # home position
            print('home')
            arm.home()

        elif event.name == 'l' and event.event_type == 'down': # gripper grab
            print('grab')
            arm.grab()

        elif event.name == 'k' and event.event_type == 'down': # gripper release
            print('release')
            arm.release()
            
        # keyboard increment
        # base
        elif event.name == 'w' and event.event_type == 'down':
            arm.increment_motor(arm.base, event.scan_code)
        elif event.name == 's' and event.event_type == 'down':
            arm.decrement_motor(arm.base, event.scan_code)
        # shoulder
        elif event.name == 'e' and event.event_type == 'down':
            arm.increment_motor(arm.shoulder, event.scan_code)
        elif event.name == 'd' and event.event_type == 'down':
            arm.decrement_motor(arm.shoulder, event.scan_code)
        
        # elbow
        elif event.name == 'r' and event.event_type == 'down':
            arm.increment_motor(arm.elbow, event.scan_code)
        elif event.name == 'f' and event.event_type == 'down':
            arm.decrement_motor(arm.elbow, event.scan_code)
        
        # wrist
        elif event.name == 't' and event.event_type == 'down':
            arm.increment_motor(arm.wrist, event.scan_code)
        elif event.name == 'g' and event.event_type == 'down':
            arm.decrement_motor(arm.wrist, event.scan_code)

        # gripper
        elif event.name == 'y' and event.event_type == 'down':
            arm.increment_motor(arm.gripper, event.scan_code)
        elif event.name == 'h' and event.event_type == 'down':
            arm.decrement_motor(arm.gripper, event.scan_code)
        
        arm.read()
        

if __name__ == '__main__':
    main()