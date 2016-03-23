clc
close

count=[];
for fileNo= 1409:1:1433
    
    fileName= num2str(fileNo);
    fullName= ['tao.' fileName ,'.0.csv'];
    snap= csvread(fullName,1,0);
    tempMass= snap(:,1);     
    id=['id' fileName];
    mass.(id)=tempMass;

    i=fileNo-1408;
    count(i)=numel(tempMass);
    
    
end

z=csvread('redshift.txt');
z=fliplr((z(7:31,:))');

plot(z,count/500^3)
hold on

massDensity=[];
for i= 1:1:25
    
    id=['id' num2str(i+1408)];
  massDensity(i)=sum(mass.(id))/(500^3);

end
plot(z,massDensity)

title('Full snapshot density against redshift')
xlabel('Redshift')
ylabel('Stellar Mass density $$(M_{\odot}^{10} Mpc^{-3})$$ / Number Density $$(Mpc^{-3})$$','interpreter','latex')
legend( 'Number Density', ' Stellar Mass density')

