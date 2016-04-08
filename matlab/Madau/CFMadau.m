clc
close

h=0.73;
simVol=(500/h)^3;

%% Reading in density & redshift from Millenium

count=zeros(1,25);
rho=zeros(1,25);
for fileNo= 1409:1:1433
    
    fileName= num2str(fileNo);
    fullName= ['tao.' fileName ,'.0.csv'];
    snap= csvread(fullName,1,0);
    tempMass= snap(:,1);     
    
    i=fileNo-1408;
    rho(i)= sum(tempMass)/simVol;
    disp(i)
end

z= csvread('redshiftStep.txt');
z=fliplr((z(7:31,:))');

%% Reading in from GAMA

gama=csvread('GAMA.csv',1,0);
gz=gama(:,1);
gLogMass=gama(:,2);

%converting log mass to solar masses to the 10
gMass=(10.^gLogMass)*10^(-10);
%preallocation of the size of arrays
stepDist=zeros(1,13);
grho=zeros(1,12);
stepz=zeros(1,12);

for i=1:12  
    %steps in redshift (from 0 to 0.6 in steps of 0.05
    stepz(i)=i/20;
    %mapping galaxies within the redshift range
    stepMap= gz < stepz(i) & gz>stepz(i)-0.5;
    stepMass= sum(gMass(stepMap,:));
    %Finding distance between redshift steps (stepz(i) here is the lower
    %limit as we are allocating stepDist (i+1) and as we have preallocated an array of zeros, the distance to the first redshift step will be zero)
    stepDist(i+1)=stepz(i)*(stepz(i)+1)*3e8/(73e3);
    %the volume of 
    stepVol=(286/41252.96)*(4/3)*pi*(stepDist(i+1)^3-stepDist(i)^3);
    grho(i)=stepMass/stepVol;    
end

%% Reading in from SDSS
%preallocate size of arrays
passDist=zeros(1,9);
passRho=zeros(1,9);
passStep=zeros(1,9);

for fileNo = 1:9 %redshifts 0.1-0.9
    %read in files
i=fileNo;
fileName=num2str(fileNo);
fullName=['C:\Users\user\Documents\LightconeMatlabBS\SDSS\SDSSPassive0',fileName,'.csv'];
SDSSP=csvread(fullName,2,0);
%redshift of galaxies
passz=SDSSP(:,1);
%redshift of segment
passStep(i)=i/10;
%converting log mass to solar masses to the 10
passLogMass=SDSSP(:,2);
passMass=(10.^passLogMass)*10^(-10);
%Finding distance between redshift steps, the volume and density
passDist(i+1)=(passStep(i))*((passStep(i))+1)*3e8/(73e3);
passVol=(14555/41252.96)*(4/3)*pi*(passDist(i+1)^3-passDist(i)^3);
passRho(i)=sum(passMass)/passVol;

end

%repeating for the forming selection
actDist=zeros(1,9);
actRho=zeros(1,9);
actStep=zeros(1,9);
for fileNo = 1:9
i=fileNo;
fileName=num2str(fileNo);
fullName=['C:\Users\user\Documents\LightconeMatlabBS\SDSS\SDSSForming0',fileName,'.csv'];
SDSSA=csvread(fullName,2,0);
actz=SDSSA(:,1);
actStep(i)=i/10;
actLogMass=SDSSA(:,2);
actMass=(10.^actLogMass)*10^(-10);
actDist(i+1)=(actStep(i))*((actStep(i))+1)*3e8/(73e3);
actVol=(14555/41252.96)*(4/3)*pi*(actDist(i+1)^3-actDist(i)^3);
actRho(i)=sum(actMass)/actVol;

end


%% plotting gradients

%GAMA
hold off 
gfitresult = GAMAfit(stepz, grho);
diffGAMA=differentiate(gfitresult, stepz);
yGAMA=log10(diffGAMA);
ryGAMA=real(yGAMA);
l=(0.02305.*stepz);
u=(0.07153.*stepz);


%millenium 
mfitresult = GAMAfit(z, rho);
diffMIL=differentiate(mfitresult, z);
yMIL=log10(diffMIL);

%SDSS passive
SDSSPfitresult = SDSSfit(passStep, passRho);
diffSDSSP=differentiate(SDSSPfitresult, passStep);
ySDSSP=log10(diffSDSSP);

%SDSS active
SDSSAfitresult = SDSSfit(actStep, actRho);
diffSDSSA=differentiate(SDSSAfitresult, actStep);
ySDSSA=log10(diffSDSSA);

errorbar(stepz, ryGAMA,l,u );
hold on
plot(z,yMIL);
plot(passStep, ySDSSP);
plot(actStep, ySDSSA);

legend('gama','mil','pass','act')







