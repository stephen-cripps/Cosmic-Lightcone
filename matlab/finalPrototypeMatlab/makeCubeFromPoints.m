function [cube] = makeCubeFromPoints(p)
%makeCubeFromPoints 
% makes a cube that encloses all points

cube.x = min(p.x);
cube.y = min(p.y);
cube.z = min(p.z);

cube.w = max(p.x) - cube.x;
cube.h = max(p.y) - cube.y;
cube.d = max(p.z) - cube.z;

cube = drawCube(cube);

end

