function [ gInCone] = getInCone(g, obs, l)
%getinCone
% The 3D function computers which galaxies are inside the cone
% All supplied and return variables are structures
% g - input galaxies, with x, y, and z coordinates
% obs - observer position, x,y, and z coordinates
% l - lightcone, inclues r, theta, phi and opening angle

% g - returns with the coordinates of the galaxies inside the cone


% First shift all galaxies where the observer is at the origin
g.x = g.x - obs.x;
g.y = g.y - obs.y;
g.z = g.z - obs.z;


% Performe two reference frame rotation to align the z axis with the line
% of sight
% rotation around the z axis, clockwise by phi
gbar.x = g.x .* cos(-l.phi) - g.y .* sin(-l.phi);
gbar.y = g.x .* sin(-l.phi) + g.y .* cos(-l.phi);
gbar.z = g.z;

% rotation around the y-axis, clockwise, by theta
% same as counter-clockwise by -theta
gp.x = gbar.x .* cos(-l.theta) + gbar.z .* sin(-l.theta);
gp.y = gbar.y;
gp.z = - gbar.x .* sin(-l.theta) + gbar.z .* cos(-l.theta);


% Convert it to sphereical polar
g.r = sqrt(gp.x .^ 2 + gp.y .^ 2 + gp.z .^ 2);
g.theta = real(acos(gp.z ./ g.r));
% Don't need phi

gInCone.x = [];
gInCone.y = [];
gInCone.z = [];

% Fine which galaxies are inside the cone
for i = 1:length(g.x)
    if g.theta(i) <= l.o && g.r(i) <= l.r
        gInCone.x = [gInCone.x, g.x(i)];
        gInCone.y = [gInCone.y, g.y(i)];
        gInCone.z = [gInCone.z, g.z(i)];
    end
end


% Shift the galaxies back
% First shift all galaxies where the observer is at the origin
gInCone.x = gInCone.x + obs.x;
gInCone.y = gInCone.y + obs.y;
gInCone.z = gInCone.z + obs.z;

end

