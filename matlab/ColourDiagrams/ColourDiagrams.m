clc 
close

% snapshot=csvread('tao.1433.0.csv',1,0);

u=snapshot(:,9);
r=snapshot(:,11);

difference=u-r;

bins=100;
[y,x] = hist(difference,bins); 
y = y/sum(y);
plot(x,y); 

title('Colour Separated Galaxy types at z=1.1734')
xlabel('M_u-M_r')
ylabel('Abundance')
hold on

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

yrange=y(ib:ir);
[minVal, position] = min(yrange);
position= position + ib;
minima = x(position);


plot([bmaxima, bmaxima], [0, max(y)], 'b')
plot([minima, minima], [0, max(y)], 'g')
plot([rmaxima, rmaxima], [0, max(y)], 'r')



