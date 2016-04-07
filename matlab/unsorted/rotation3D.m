clear;
close;
clc;

% Assume observer at the origion
% Generation of random points within range
% These points are used as example of galaxies
range = 10;
size = 100;
% g_x = rand(1, size).*2.*range - range;
% g_y = rand(1, size).*2.*range - range;
% g_z = rand(1, size).*2.*range - range;


% Define the lightcone 
r_l = range;
theta_l = pi/4;
phi_l = pi/4;
theta_o = pi/12;

% Line of Sight 
r = linspace(0, r_l, size);
g_x = r .* sin(theta_l) .* cos(phi_l);
g_y = r .* sin(theta_l) .* sin(phi_l);
g_z = r .* cos(theta_l);

axisRange = [0, range];

h=figure(1)
set(h, 'Position', [0 0 1400 360])
subplot(1,3,1)
plot3(g_x, g_y, g_z, 'r')
xlim(axisRange)
ylim(axisRange)
zlim(axisRange)
xlabel('X')
ylabel('Y')
zlabel('Z')

%% Reference Frame Rotation

% rotation around the z axis, counter-clockwise by phi_i
g_x_bar = g_x .* cos(-phi_l) - g_y .* sin(-phi_l);
g_y_bar = g_x .* sin(-phi_l) + g_y .* cos(-phi_l);
g_z_bar = g_z;
subplot(1,3,2)
plot3(g_x_bar, g_y_bar, g_z_bar, 'r')
xlim(axisRange)
ylim(axisRange)
zlim(axisRange)
xlabel('XBar')
ylabel('YBar')
zlabel('ZBar')

% rotation around the y-axis, clockwise, by theta_i
% same as counter-clockwise by -theta_i
g_x_p = g_x_bar .* cos(-theta_l) + g_z_bar .* sin(-theta_l);
g_y_p = g_y_bar;
g_z_p = - g_x_bar .* sin(-theta_l) + g_z_bar .* cos(-theta_l);
subplot(1,3,3)
plot3(g_x_p, g_y_p, g_z_p, 'r')
xlim(axisRange)
ylim(axisRange)
zlim(axisRange)
xlabel('Xp')
ylabel('Yp')
zlabel('Zp')


