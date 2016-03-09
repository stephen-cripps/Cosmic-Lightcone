clear
clc;

%%

x1 = csvread('464.11.106.230.csv');

figureSize = [100, 100, 960, 380];

%% 2,60,149
x = 11;
y = 106;
z = 230;
f1 = figure(1);
set(f1, 'Position', figureSize);
subplot(1,2,1)
plot(x1(:,1)-x, x1(:,3)-z, '.');
xlim([-10 10])
ylim([-10 10])
xlabel('SGX (Mpc)')
ylabel('SGZ (Mpc)')
rectangle('position',[-10,-10,20,20],'curvature',[1,1],'linestyle','-','edgecolor','b');
%rectangle('Position',[0 0 10 10],'Curvature',[1 1]);
subplot(1,2,2)
plot(x1(:,2)-y, x1(:,3)-z, '.');
xlim([-10 10])
ylim([-10 10])
xlabel('SGY (Mpc)')
ylabel('SGZ (Mpc)')
rectangle('position',[-10,-10,20,20],'curvature',[1,1],'linestyle','-','edgecolor','b');