clear;
clc;
clf;

% Galaxies selection in 3D
% Generation of random points within boxSize
% These points are used as example of galaxies

boxSize = 10;
size = 100000;
g.x = rand(1, size) .* boxSize;
g.y = rand(1, size) .* boxSize;
g.z = rand(1, size) .* boxSize;

% define observer
% obs.x = rand * boxSize;
% obs.y = rand * boxSize;
% obs.z = rand * boxSize;
obs.x = boxSize/2;
obs.y = boxSize/2;
obs.z = boxSize/2;


%for i = linspace(0, pi, 300)
% Define the lightcone 
l.r = boxSize/2;
l.theta = pi/4;
l.phi = pi;
l.o = pi/6;

gInCone = getInCone(g, obs, l);

snapCube = makeCube(0, 0, 0, boxSize, boxSize, boxSize );

% Define the 5 points of the reverse pyramid in the rotated frame
d = l.r * tan(l.o);
p.x = [-1, 1, 1, -1, 0] .* d;
p.y = [1, 1, -1, -1, 0] .* d;
p.z = [1, 1, 1, 1, 0] .* l.r;

% Reverse rotation
% rotation around the y-axis, clockwise, by theta
% same as counter-clockwise by -theta
pbar.x = p.x .* cos(l.theta) + p.z .* sin(l.theta);
pbar.y = p.y;
pbar.z = - p.x .* sin(l.theta) + p.z .* cos(l.theta);
% rotation around the z axis, clockwise by phi
p.x = pbar.x .* cos(l.phi) - pbar.y .* sin(l.phi);
p.y = pbar.x .* sin(l.phi) + pbar.y .* cos(l.phi);
p.z = pbar.z;
p.x = p.x + obs.x;
p.y = p.y + obs.y;
p.z = p.z + obs.z;

coneCube = makeCubeFromPoints(p);

%% Main Plot 
subplot(2,3,1)
plotLim = 300;
scatter3(g.x(1:plotLim), g.y(1:plotLim), g.z(1:plotLim), '.');
hold on;
plot3(snapCube.dx, snapCube.dy, snapCube.dz, 'k')
plot3(coneCube.dx, coneCube.dy, coneCube.dz, 'r')
scatter3(gInCone.x, gInCone.y, gInCone.z, 'r.');
%axisRange = [-0.1, boxSize + 0.];
axis equal;
% xlim(axisRange)
% ylim(axisRange)
% zlim(axisRange)
xlabel('X')
ylabel('Y')
zlabel('Z')
%Show observer in green
scatter3(obs.x, obs.y, obs.z, 'ro');
hold off;

subplot(2,3,2)
scatter3(gInCone.x, gInCone.y, gInCone.z, '.');
hold on;
plot3(snapCube.dx, snapCube.dy, snapCube.dz, 'k')
plot3(coneCube.dx, coneCube.dy, coneCube.dz, 'r')
axis equal;
% xlim(axisRange)
% ylim(axisRange)
% zlim(axisRange)
xlabel('X')
ylabel('Y')
zlabel('Z')
%Show observer in green
scatter3(obs.x, obs.y, obs.z, 'ro');
hold off;

axisRange = [0, boxSize];

subplot(2,3,4)
scatter(gInCone.x, gInCone.y, '.');
hold on;
plot(snapCube.dx, snapCube.dy, 'k')
plot(coneCube.dx, coneCube.dy, 'r')
scatter(obs.x, obs.y, 'ro')
xlim(axisRange)
ylim(axisRange)
xlabel('X')
ylabel('Y')
hold off;


subplot(2,3,5)
scatter(gInCone.x, gInCone.z, '.');
hold on;
plot(snapCube.dx, snapCube.dz, 'k')
plot(coneCube.dx, coneCube.dz, 'r')
scatter(obs.x, obs.z, 'ro')
xlim(axisRange)
ylim(axisRange)
xlabel('X')
ylabel('Z')
hold off;


subplot(2,3,6)
scatter(gInCone.y, gInCone.z, '.');
hold on;
plot(snapCube.dy, snapCube.dz, 'k')
plot(coneCube.dy, coneCube.dz, 'r')
scatter(obs.y, obs.z, 'ro')
xlim(axisRange)
ylim(axisRange)
xlabel('Y')
ylabel('Z')
hold off;

pause(0.1)
%end
