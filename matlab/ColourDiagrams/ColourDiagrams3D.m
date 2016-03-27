clc
close
% 
% for fileNo= 1409:1:1433
%     
%     %Reading in snapshot
%     fileName= num2str(fileNo);
%     fullName= ['tao.' fileName ,'.0.csv'];
%     snapshot= csvread(fullName,1,0);
%     
%     %Extracting Mu and Mr
%     u=snapshot(:,9);
%     r=snapshot(:,11);
% 
%     %Creating an array of histogram data for each snapshot
%     difference=u-r;
%     i=fileNo-1408;
%     bins=100;
%     %Initial bin widths
%    if i == 1
%     [ytemp,x] = hist(difference,bins); 
%     y(i,:) = ytemp/sum(ytemp);
%    else
%     ytemp = hist(difference,x); 
%     y(i,:) = ytemp/sum(ytemp);
%    end
%    
%     disp(i)
% end
% 
% z=csvread('redshift.txt');
% z=fliplr((z(7:31,:))');
% x=meshgrid(x);

surf(x(1:25,:),z,y)
xlabel('u-r')
ylabel('z')
zlabel('abundance')
title('Evolution of the separation of galaxy types')