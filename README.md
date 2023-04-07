# ME380 Robot Arm Project - Group 7

The goal of the project is to build a pick and place robot manipulator. Our group chose 2 specifc deisgn objectives: autonomous functionality & high strength-to-weight ratio

Group Roles:
- Project Management: David Acosta
- Manipulator: Aimen Shaikh
- Gripper: Lauren Kissoon
- Controls & Software: Adam Iantorno
- Electrical & Actuation: Vlad Nica

## Repository Setup

### Python

After you clone the repository onto your local computer. You need to setup a python virtualenvironment to install the required dependencies (or you can install them to your local computer).

First, ensure that you have python install and the virutalenv library installed:
```
pip install virtualenv
```

Before you follow the next steps, make sure you are within the repository's directory. 

Next, you want to create your virtual envrionment, activate it, and install the required dependencies. 
```
virtualenv {environment_name}
. <environment_name>/Scripts/activate
pip install -r requirements.txt
```

If you add any new python dependencies to the project, make sure you export a new requirements file (from the project's home directory)
```
pip freeze --local > requirements.txt
```

To deactivate your virtual environment
```
deactivate
```

### Arduino

There are two external libraries you need to install from Arduino's library manager:
- AccelStepper by MikeMcCauley
- Adafruit PWM Servo Driver Library by Adafruit

## Hardware

- 1 x Arduinop MEGA
- 1 x Stepper Motor:
- 1 x Stepper Motor:
- 2 x Stepper Motor Driver: 
- 3 x Servo Motor:
- 1 x Adafruit Driver:

# Arduino Setup for Breakboard control
## Servo
- Gripper: A10
- Wrist: A9
- Elbow: A8
- Direction Control: A11

- Grippper Ada:
- Wrist Ada:
- Elbow Ada:

## Stepper
- Base Setup: 22, 24, 26, 28 (yellow first)
- Base Forward: 32
- Base Backward: 34

- Shoulder Setup: 23, 25, 27, 29
- Shoulder Forward: 45
- Shoulder Backward: 47

