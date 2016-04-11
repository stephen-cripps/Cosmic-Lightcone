clc 
close

snapshot=csvread('tao.1409.0.csv',1,0);

u=snapshot(:,9);
r=snapshot(:,11);
difference=u-r;
x=r-5*log10(0.73);


%No longer used as exporting to topcat for better graph
% values=hist3([difference x],[1000 1000]);
% contour(values)
% 
% title('colour magnitude plot at z=1.1734')
% ylabel('M_u-M_r')
% xlabel('M_r-5logh')

m=[x,difference];
csvwrite('ColMagMil0.csv',m)