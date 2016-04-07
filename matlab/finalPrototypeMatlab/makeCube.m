function [ cube] = makeCube( x, y, z, w, h, d)
%makeCube Summary of this function goes here
%   Detailed explanation goes here

cube.x = x;
cube.y = y;
cube.z = z;
cube.w = w;
cube.h = h;
cube.d = d;

cube = drawCube(cube);

end

