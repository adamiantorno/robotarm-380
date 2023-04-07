# Software Developped for ME 380 Project at the University of Waterloo - Group 7

import numpy as np

import parameters as par

def calculate_angle(coord_x, coord_y):
    dist = np.sqrt(coord_x**2 + coord_y**2)
    dist_xy =  np.sqrt(coord_x**2 + coord_y**2) - par.BASE_HEIGHT
    base_angle = np.arctan2(coord_y, coord_x)

    alpha = np.acos((par.SH_L**2 + par.ELB_L**2 - dist**2)/(2*par.SH_L*par.ELB_L))
    beta = np.atan2(0, dist_xy)
    gamma = np.acos((dist_xy**2 + par.SH_L**2 - par.ELB_L**2) / (2*dist*par.SH_L))

    # Calculate angle
    theta2_1 = beta - gamma
    theta2_2 = beta + gamma
    theta3_1 = np.pi - alpha
    theta3_2 = -1 * (np.pi - alpha)

    # Choose largest shoulder angle
    if theta2_1 > theta2_2:
        shoulder_angle = theta2_1
        elbow_angle = theta3_1
    else:
        shoulder_angle = theta2_2
        elbow_angle = theta3_2
    
    return base_angle, shoulder_angle, elbow_angle
    

