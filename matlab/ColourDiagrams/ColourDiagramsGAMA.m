clc 
close

data=csvread('GAMA_colour.csv',1,0); %read in data

%Define columns and map redshift range
z=data(:,1);
u=data(:,2);
r=data(:,4);
map=z>=0.35 & z<=0.5 ; 
%apply map to data
u=u(map);
r=r(map);

difference=u-r;

bins=100;
[y,x] = hist(difference,bins); 
y = y/sum(y);
plot(x,y); 

axis([0 3.5 0 0.06])
title('Colour Separated Galaxy types at 0.35<z<0.5 for GAMA')
xlabel('M_u-M_r')
ylabel('Abundance')
hold on






