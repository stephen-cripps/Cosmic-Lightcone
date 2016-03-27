clc 
close
% 
% 
% for fileNo= 1409:1:1433
%     
%     fileName= num2str(fileNo);
%     fullName= ['tao.' fileName ,'.0.csv'];
%     snapshot= csvread(fullName,1,0);
% 
% u=snapshot(:,9);
% r=snapshot(:,11);
% 
% difference=u-r;
% 
% bins=100;
% [y,x] = hist(difference,bins); 
% y = y/sum(y);
% 
% bmaxima = 0;
% for i=2:bins-1
%    
%     
%     if y(i)>y(i-1) && y(i)> y(i+1) && bmaxima == 0 && y(i)>0.01
%         bmaxima=x(i);
%         ib= i;
%         elseif y(i)>y(i-1) && y(i)> y(i+1) &&y(i)>0.01
%         rmaxima=x(i);
%         ir = i;
%     
%     end
% end
% 
% yrange=y(ib:ir);
% [minVal, position] = min(yrange);
% position= position + ib;
% minima = x(position);
% 
% ratio(fileNo-1408)=sum(y(1:position))/sum(y(position:100));
% 
% end
% 
% z=csvread('redshift.txt');
% z=fliplr((z(7:31,:))');

plot(z,ratio);
title('Ratio of Active to Passive Galaxies vs. redshift')
ylabel('Active:Passive')
xlabel('z')

