clc 
close

 snapshot=csvread('SDSS/colour01.csv',2,0);
% 
 mass= snapshot(:,1);
 SDSSu=snapshot(:,2);
 SDSSr=snapshot(:,3);
map= mass > 0.1 & SDSSu > -100 & SDSSu <-17.5;
 SDSSu=SDSSu(map);
 SDSSr=SDSSr(map);
 difference=SDSSu-SDSSr;
 x=SDSSr-5*log10(0.73);
 

% 
% %Removing outliers for SDSS data
% map= difference >-100;
% difference=difference(map);
 %x=x(map);

%No longer used as exporting to topcat for better graph
% values=hist3([difference x],[1000 1000]);
% contour(values)
% 
% title('colour magnitude plot at z=1.1734')
% ylabel('M_u-M_r')
% xlabel('M_r-5logh')

m=[x,difference];
csvwrite('ColourMagOutputs/SDSSMagLim.csv',m)

disp('done it m8')