function [ figHandle ] = makeSGC(str, x, y, z)
% makeSGC Generates a SGX vs SGX and SGY vs SGZ
% str - path and name of the file 
% x, y, z - center of the observer 

figureConfig= [100, 100, 960, 380];
M = csvread(str);
size = 10;
lim = [-size size];
circleConfig = [-size,-size,size*2,size*2];
% Left SGX vs SGZ
figHandle = figure();
set(figHandle, 'Position', figureConfig);
subplot(1,2,1)
plot(M(:,1)-x, M(:,3)-z, '.');
xlim(lim)
ylim(lim)
xlabel('SGX (Mpc)')
ylabel('SGZ (Mpc)')
rectangle('position', circleConfig,'curvature',[1,1],'linestyle','-','edgecolor','b');
% Right SGY vs SGZ
subplot(1,2,2)
plot(M(:,2)-y, M(:,3)-z, '.');
xlim(lim)
ylim(lim)
xlabel('SGY (Mpc)')
ylabel('SGZ (Mpc)')
rectangle('position', circleConfig,'curvature',[1,1],'linestyle','-','edgecolor','b');
end

