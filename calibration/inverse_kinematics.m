
% Define the distances between the joints
D1 = 10; % Distance between joint 1 and joint 2
D2 = 8; % Distance between joint 2 and joint 3
D3 = 6; % Distance between joint 3 and the end effector

% Define the desired end effector position
x = 15; % Distance of the end effector from the base in the x direction
y = 5; % Distance of the end effector from the base in the y direction

% Calculate the distance between the base and the end effector
dist = sqrt(x^2 + y^2);

% Calculate the angle between the base and the end effector
theta1 = atan2(y,x);

% Calculate the angles of the joints using inverse kinematics
[theta2, theta3] = inverseKinematics(dist, D1, D2, D3);

% Print the angles
disp(['theta1 = ', num2str(theta1)]);
disp(['theta2 = ', num2str(theta2)]);
disp(['theta3 = ', num2str(theta3)]);