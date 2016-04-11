<<<<<<< HEAD
clear;
close;
clc;
clf;

% Galaxies selection in 3D
% Assume observer at the origion
% Generation of random points within range
% These points are used as example of galaxies

range = 10;
size = 10000;
g_x = rand(1, size).*2.*range - range;
g_y = rand(1, size).*2.*range - range;
g_z = rand(1, size).*2.*range - range;

% Define the lightcone 
r_l = 2*range;
theta_l = pi/2;
phi_l = pi/2;
theta_o = pi/6;

axisRange = [-range, range];

% Reference Frame Rotation
% rotation around the z axis, clockwise by phi_i
g_x_bar = g_x .* cos(-phi_l) - g_y .* sin(-phi_l);
g_y_bar = g_x .* sin(-phi_l) + g_y .* cos(-phi_l);
g_z_bar = g_z;

% rotation around the y-axis, clockwise, by theta_i
% same as counter-clockwise by -theta_i
g_x_p = g_x_bar .* cos(-theta_l) + g_z_bar .* sin(-theta_l);
g_y_p = g_y_bar;
g_z_p = - g_x_bar .* sin(-theta_l) + g_z_bar .* cos(-theta_l);

% Convert it to sphereical polar 
g_r = sqrt(g_x_p .^ 2 + g_y_p .^ 2 + g_z_p .^ 2);
g_theta = real(acos(g_z_p ./ g_r));
% Don't need phi 

% Check and extract points inside the cone
g_x_inCone = [];
g_y_inCone = [];
g_z_inCone = [];
for i = 1:size
    if g_theta(i) <= theta_o
        g_x_inCone(i)  = g_x(i);
        g_y_inCone(i)  = g_y(i);
        g_z_inCone(i)  = g_z(i);
    end
end



% Main Plot 
subplot(2,2,1)
scatter3(g_x(1:0.1*size), g_y(1:0.1*size), g_z(1:0.1*size), '.');
hold on;
xlim(axisRange)
ylim(axisRange)
zlim(axisRange)
xlabel('X')
ylabel('Y')
zlabel('Z')

% plot galaxies inside the cone as red
scatter3(g_x_inCone, g_y_inCone, g_z_inCone, 'r.');
hold off;

subplot(2,2,2)
scatter3(g_x_inCone, g_y_inCone, g_z_inCone, '.');
xlim(axisRange)
ylim(axisRange)
zlim(axisRange)
xlabel('X')
ylabel('Y')
zlabel('Z')

subplot(2,2,3)
scatter(g_x_inCone, g_y_inCone, '.');
xlim(axisRange)
ylim(axisRange)
xlabel('X')
ylabel('Y')

subplot(2,2,4)
scatter(g_y_inCone, g_z_inCone, '.');
xlim(axisRange)
ylim(axisRange)
xlabel('Y')
ylabel('Z')





=======
clear;
close;
clc;
clf;

% Galaxies selection in 3D
% Assume observer at the origion
% Generation of random points within range
% These points are used as example of galaxies

range = 10;
size = 10000;
g_x = rand(1, size).*2.*range - range;
g_y = rand(1, size).*2.*range - range;
g_z = rand(1, size).*2.*range - range;

% Define the lightcone 
r_l = 2*range;
theta_l = pi/2;
phi_l = pi/2;
theta_o = pi/6;

axisRange = [-range, range];

% Reference Frame Rotation
% rotation around the z axis, clockwise by phi_i
g_x_bar = g_x .* cos(-phi_l) - g_y .* sin(-phi_l);
g_y_bar = g_x .* sin(-phi_l) + g_y .* cos(-phi_l);
g_z_bar = g_z;

% rotation around the y-axis, clockwise, by theta_i
% same as counter-clockwise by -theta_i
g_x_p = g_x_bar .* cos(-theta_l) + g_z_bar .* sin(-theta_l);
g_y_p = g_y_bar;
g_z_p = - g_x_bar .* sin(-theta_l) + g_z_bar .* cos(-theta_l);

% Convert it to sphereical polar 
g_r = sqrt(g_x_p .^ 2 + g_y_p .^ 2 + g_z_p .^ 2);
g_theta = real(acos(g_z_p ./ g_r));
% Don't need phi 

% Check and extract points inside the cone
g_x_inCone = [];
g_y_inCone = [];
g_z_inCone = [];
for i = 1:size
    if g_theta(i) <= theta_o
        g_x_inCone(i)  = g_x(i);
        g_y_inCone(i)  = g_y(i);
        g_z_inCone(i)  = g_z(i);
    end
end



% Main Plot 
subplot(2,2,1)
scatter3(g_x(1:0.1*size), g_y(1:0.1*size), g_z(1:0.1*size), '.');
hold on;
xlim(axisRange)
ylim(axisRange)
zlim(axisRange)
xlabel('X')
ylabel('Y')
zlabel('Z')

% plot galaxies inside the cone as red
scatter3(g_x_inCone, g_y_inCone, g_z_inCone, 'r.');
hold off;

subplot(2,2,2)
scatter3(g_x_inCone, g_y_inCone, g_z_inCone, '.');
xlim(axisRange)
ylim(axisRange)
zlim(axisRange)
xlabel('X')
ylabel('Y')
zlabel('Z')

subplot(2,2,3)
scatter(g_x_inCone, g_y_inCone, '.');
xlim(axisRange)
ylim(axisRange)
xlabel('X')
ylabel('Y')

subplot(2,2,4)
scatter(g_y_inCone, g_z_inCone, '.');
xlim(axisRange)
ylim(axisRange)
xlabel('Y')
ylabel('Z')





>>>>>>> 88c8c332f26f3ad6a81e823607e88bb1ace80267
