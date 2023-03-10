# ME380 Robot Arm Project - Group 7

The goal of the project is to build a pick and place robot manipulator. Our group chose 2 specifc deisgn objectives: autonomous functionality & high strength-to-weight ratio

Group Roles:
- Project Management: David Acosta
- Manipulator: Aimen Shaikh
- Gripper: Lauren Kissoon
- Controls & Software: Adam Iantorno
- Electrical & Actuation: Vlad Nica

## Repository Setup

After you clone the repository onto your local computer. You need to setup a python virtualenvironment to install the required dependencies (or you can install them to your local computer).

First, ensure that you have python install and the virutalenv library installed:
```
pip install virtualenv
```

Before you follow the next steps, make sure you are within the repository's directory. 

Next, you want to create your virtual envrionment, activate it, and install the required dependencies. 
```
virtualenv {environment_name}
<environment_name>/Scripts/activate
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
