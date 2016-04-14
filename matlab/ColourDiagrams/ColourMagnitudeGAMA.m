clc 
close

%read in data
data=csvread('GAMA_colour.csv',1,0); 

%Define columns and map redshift range
z=data(:,1);
logmass=data(:,2);
u=data(:,4);
r=data(:,6);
map=z>=0 & z<=0.1; 

%apply map to data
u=u(map);
r=r(map);
logmass=logmass(map);

% %generate values for plotting
 difference=u-r;
 x=r-5*log10(0.73);
% values=hist3([difference x],[50 50]);
% 
% %plot
% contour(values)
% title('colour magnitude plot at z<0.1')
% ylabel('M_u-M_r')
% xlabel('M_r-5logh')

m=[x,difference];
csvwrite('ColMagGam01.csv',m)