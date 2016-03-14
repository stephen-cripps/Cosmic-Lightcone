clear;
clc;
close;
%% Lightcone checking function

obsX = 12;
obsY = 24;

% Generation of random points within range
% These points are used as example of galaxies
range = 10;
size = 1000;
x = rand(1, size).*2.*range - range + obsX;
y = rand(1, size).*2.*range - range + obsY;

% Caluclating the Polar coordinates of the points
gr = sqrt((x - obsX).^2 + (y - obsY).^2);
theta_g = zeros(1, size);

for i = 1 : size
    if(x(i) - obsX >0)
        theta_g(i) = atan((y(i) - obsY)/(x(i) - obsX));
    elseif(x(i) - obsX<0)
        if y(i) - obsY >=0
            theta_g(i) = atan((y(i) - obsY)/(x(i) - obsX)) + pi;
        else
            theta_g(i) = atan((y(i) - obsY)/(x(i) - obsX)) - pi;
        end
    else
        if y(i) - obsY >0
            theta_g(i) = pi/2;
        else
            theta_g(i) = -pi/2;
        end
    end
end
theta_g = mod(theta_g+2.*pi, 2.*pi);

% Function describes the line of the sight, L
Lx = @(r, theta_l) r.*cos(theta_l) + obsX;
Ly = @(r, theta_l) r.* sin(theta_l)+ obsY;

% Upper Boundary, B+
Bpx = @(r, theta_l, theta) r.*cos(theta_l + theta)+ obsX;
Bpy = @(r, theta_l, theta) r.*sin(theta_l + theta)+ obsY;

% Lower Boundary, B-
Bmx = @(r, theta_l, theta) r.*cos(theta_l - theta)+ obsX;
Bmy = @(r, theta_l, theta) r.*sin(theta_l - theta)+ obsY;


% Define the lightcone
theta_l = 0;  % lightcone inclide angle
theta = pi/12;  % lightcone opening angle
rMax = range;
r = linspace(0, rMax);


%% Visualisation
animationRange = 100;
figure(1)
for j = 1:animationRange
    % Increment the lightcone for animation 
    theta_l = theta_l + 0.1;
    theta_l = mod(theta_l+2*pi, 2*pi);
    
    % Core Plot
    plot(x,y, '.');
    hold on;
    axis equal;
    xlim([obsX-range obsX+range])
    ylim([obsY-range obsY+range])
    
    % Plot the lightcone L, B+, B-
    plot(Lx(r, theta_l), Ly(r, theta_l), 'k')
    plot(Bpx(r, theta_l, theta), Bpy(r, theta_l, theta), 'r')
    plot(Bmx(r, theta_l, theta), Bmy(r, theta_l, theta), 'r')
    rectangle('position', [obsX-range obsY-range range*2 range*2],'curvature',[1,1],'linestyle','-','edgecolor','b');
    
    % Array of galaxies inside the lightcone
    inConeX = [];
    inConeY = [];
    
    % Core Checking Methods
    if theta_l < theta  || theta_l > 2*pi - theta
        % Around the positive x-axis
        for i = 1:size
            if(gr(i) <= rMax && (theta_g(i) <= mod(theta_l +theta, 2*pi) || theta_g(i) >= mod(theta_l - theta + 2*pi, 2*pi)))
                inConeX = [inConeX, x(i)];
                inConeY = [inConeY, y(i)];
            end
        end
    else
        for i = 1:size
            if(gr(i) <= rMax && theta_g(i) <= theta_l + theta && theta_g(i) >= theta_l - theta)
                inConeX = [inConeX, x(i)];
                inConeY = [inConeY, y(i)];
            end
        end
    end
    plot(inConeX,inConeY, 'bx');
    title(['Observer at (', num2str(obsX), ', ', num2str(obsY), ')'])
    hold off;
    pause(0.05)
end