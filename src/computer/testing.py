
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
        if event.name == 'p' and event.event_type == 'down': # pickup
            print('pick up')
            # arm.move_to()

        elif event.name =='o' and event.event_type == 'down': # dropoff
            print('dropoff')
            arm.move_to(par.BASE_DROP, par.SH_DROP, par.ELB_DROP, par.WRIST_DROP, par.GRIP_DROP, forward=False)

        elif event.name == 'i' and event.event_type == 'down': # home position
            print('home')
            arm.move_to(par.BASE_HOME, par.SH_HOME, par.ELB_HOME, par.WRIST_HOME, par.GRIP_HOME, forward=False)

        elif event.name == 'l' and event.event_type == 'down': # gripper grab
            print('grab')
            arm.grab()

        elif event.name == 'r' and event.event_type == 'down': # gripper release
            print('release')
            arm.release()
            
        # keyboard increment
        # base
        elif event.name == 'w' and event.event_type == 'down':
            arm.base.increment()
        elif event.name == 's' and event.event_type == 'down':
            arm.base.decrement()
        
        # shoulder
        elif event.name == 'e' and event.event_type == 'down':
            arm.shoulder.increment()
        elif event.name == 'd' and event.event_type == 'down':
            arm.shoulder.decrement()
        
        # elbow
        elif event.name == 'r' and event.event_type == 'down':
            arm.elbow.increment()
        elif event.name == 'f' and event.event_type == 'down':
            arm.elbow.decrement()
        
        # wrist
        elif event.name == 't' and event.event_type == 'down':
            arm.wrist.increment()
        elif event.name == 'g' and event.event_type == 'down':
            arm.wrist.decrement()

        # gripper
        elif event.name == 'y' and event.event_type == 'down':
            arm.gripper.increment()
        elif event.name == 'h' and event.event_type == 'down':
            arm.gripper.decrement()
        arm.read()
        

if __name__ == '__main__':
    main()