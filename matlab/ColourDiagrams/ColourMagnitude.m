clc 
close

% snapshot=csvread('tao.1433.0.csv',1,0);

u=snapshot(:,9);
r=snapshot(:,11);
mass=snapshot(:,1);
difference=u-r;

values=hist3([difference mass],[1000 1000]);
contour(values)

title('colour magnitude plot at z=1.1734')
ylabel('M_u-M_r')
xlabel('Mass-5logh')