clear;
clc;
close;

%% Lightcone checking function
% Assume observer at the origion

% Generation of random points within range
% These points are used as example of galaxies
range = 10;
size = 1000;
g_x = rand(1, size).*2.*range - range;
g_y = rand(1, size).*2.*range - range;
g_z = rand(1, size).*2.*range - range;

figure(1)
scatter3(g_x, g_y, g_z)T
axis equal;

% Converting random points to spherical polar
g_r = sqrt(g_x.^2 + g_y.^2 + g_z.^2);
g_theta = acos(g_z./g_r);
g_phi = atan2(g_y, g_x);


% Define the lightcone 
r_l = range;
r_theta = pi/2;
r_phi = pi/2;
r_theta_o = pi/4;

