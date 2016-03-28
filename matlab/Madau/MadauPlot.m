clc
close

h=0.73;
% count=[];
% for fileNo= 1409:1:1433
%     
%     fileName= num2str(fileNo);
%     fullName= ['tao.' fileName ,'.0.csv'];
%     snap= csvread(fullName,1,0);
%     tempMass= snap(:,1);     
%     id=['id' fileName];
%     mass.(id)=tempMass;
% 
%     i=fileNo-1408;
%     count(i)=numel(tempMass);
%     
%     
% end

info=csvread('redshiftLightTravelTime.txt');
z=fliplr((info(7:31,1))');
interval= fliplr((info(7:31,2))');

massDensity=[];
for i= 1:1:25
    
    id=['id' num2str(i+1408)];
  massDensity(i)=sum(mass.(id))/((500/h)^3);

end

grad=[];
for i=1:24
    grad(i)=(massDensity(i+1)-massDensity(i))/(interval(i+1)-interval(i));  
end

plot(z(:,1:24),log10(grad))
title('Star formation rate')
xlabel('Redshift')
ylabel('$$log \dot \rho (M_\odot^{10}Mpc^{-3}Gyr^{-3})$$','interpreter','latex')


