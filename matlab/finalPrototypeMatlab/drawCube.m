function [ cube ] = drawCube( cube )
%drawCube
%sdfasdf

cube.dx = [0 1 1 0 0 0 1 1 1 1 1 1 0 0 0 0] .* cube.w + cube.x;
cube.dy = [0 0 1 1 0 0 0 0 0 1 1 1 1 1 1 0] .* cube.h + cube.y;
cube.dz = [1 1 1 1 1 0 0 1 0 0 1 0 0 1 0 0] .* cube.d + cube.z;

end

