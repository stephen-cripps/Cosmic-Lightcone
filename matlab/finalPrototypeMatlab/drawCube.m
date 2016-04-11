<<<<<<< HEAD
function [ cube ] = drawCube( cube )
%drawCube
%sdfasdf

cube.dx = [0 1 1 0 0 0 1 1 1 1 1 1 0 0 0 0] .* cube.w + cube.x;
cube.dy = [0 0 1 1 0 0 0 0 0 1 1 1 1 1 1 0] .* cube.h + cube.y;
cube.dz = [1 1 1 1 1 0 0 1 0 0 1 0 0 1 0 0] .* cube.d + cube.z;

end

=======
function [ cube ] = drawCube( cube )
%drawCube
%sdfasdf

cube.dx = [0 1 1 0 0 0 1 1 1 1 1 1 0 0 0 0] .* cube.w + cube.x;
cube.dy = [0 0 1 1 0 0 0 0 0 1 1 1 1 1 1 0] .* cube.h + cube.y;
cube.dz = [1 1 1 1 1 0 0 1 0 0 1 0 0 1 0 0] .* cube.d + cube.z;

end

>>>>>>> 88c8c332f26f3ad6a81e823607e88bb1ace80267
