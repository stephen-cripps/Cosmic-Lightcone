clc
close
% 
% count=[];
% for fileNo= 1409:1:1433
%     
%     fileName= num2str(fileNo);
%     fullName= ['tao.' fileName ,'.0.csv'];
%     snap= csvread(fullName,1,0);
%     tempMu= snap(:,9); 
%     tempMb= snap(:,10); 
%     tempMr= snap(:,11); 
%     tempMi= snap(:,12); 
%     
%     id=['id' fileName];
%     Mu.(id)= tempMu(tempMu <= -18);
%     Mb.(id)= tempMb(tempMb <= -18);
%     Mr.(id)= tempMr(tempMr <= -18);
%     Mi.(id)= tempMi(tempMi <= -18);
% 
%     i=fileNo-1408;
%     countu(i)=numel(Mu.(id));
%     countb(i)=numel(Mb.(id));
%     countr(i)=numel(Mr.(id));
%     counti(i)=numel(Mi.(id));
%     
%     
%     
% end
% 
% z=csvread('redshift.txt');
% z=fliplr((z(7:31,:))');
% 
plot(z,countu/500^3,'color',[0.5,0,0.9])
hold on
plot(z,countb/500^3,'b')
plot(z,countr/500^3,'r')
plot(z,counti/500^3,'color',[0.7,0,0])

title('Full snapshot bright galaxy (M<-18) density against redshift')
xlabel('Redshift')
ylabel('Number Density $$(Mpc^{-3})$$','interpreter','latex')
legend('U band', 'B band', 'R band', 'I band')

