clc 
close

%read in data
snapshot=csvread('MilData/tao.1424.0.csv',1,0);
u=snapshot(:,9);
r=snapshot(:,11);

%calculate y values and remove outliers
difference=u-r;
% % difference=difference(difference>-100);
% difference=difference(difference>-1);
% difference=difference(difference<6);

%create normalised histogram
bins=100;
[y,x] = hist(difference,bins); 
y = y/sum(y);
plot(x,y); 

title('Colour Separated Galaxy types at z=0.5086 (Millennium Data)')
xlabel('M_u-M_r')
ylabel('Abundance')
hold on

xlim([0 3.5])

%find maximums
bmaxima = 0;
for i=2:bins-1
   
    
    if y(i)>y(i-1) && y(i)> y(i+1) && bmaxima == 0 && y(i)>0.01
        bmaxima=x(i);
        ib= i;
        elseif y(i)>y(i-1) && y(i)> y(i+1) &&y(i)>0.01
        rmaxima=x(i);
        ir = i;
    
    end
end

%find minima
yrange=y(ib:ir);
[minVal, position] = min(yrange);
position= position + ib-1;
minima = x(position);


plot([bmaxima, bmaxima], [0, max(y)], 'b')
plot([minima, minima], [0, max(y)], 'g')
plot([rmaxima, rmaxima], [0, max(y)], 'r')


