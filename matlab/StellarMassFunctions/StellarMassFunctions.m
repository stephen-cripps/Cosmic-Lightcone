clc 
close

h=0.73;
simVol=(500/h)^3;

i=1;
%read in redshifts
redshift=csvread('redshiftStep.txt');
redshift=fliplr((redshift(7:31,:))');

%selection of files
for fileNo = [1409, 1410, 1420, 1424]

%Read in files
fileName=num2str(fileNo);
fullName=['tao.',fileName,'.0.csv'];
snapshot=csvread(fullName,1,0);

%get masses and convert to solar masses and apply limitation to match obs
%data
M=snapshot(:,1)*10^10;
M=M(M>10);
M=log10(M);

%Create normalised histogram, ignore infinite points to avoid issues in sum
[c,M]=hist(M,20);
c=log10(c/simVol);
infmap=c~=-inf;
c=c(infmap);
M=M(infmap);
%c=c/sum(c);

% Set colour depending on loop
colour=[0 0 0];
colour(:,i)=1;
%plot points
plot(M,(c),'color',colour,'linestyle','none','marker','x')
hold on
%plot smoothed lines
cs=smooth(c);
smoothed(i)=plot(M,cs,'color',colour);
%store redshifts for legend
z= redshift(:,fileNo-1408);
zs(i,:)= ['z=' sprintf('%.5f', z)];

i=i+1;
end


legend([smoothed(:,1) smoothed(:,2) smoothed(:,3) smoothed(:,4)],{zs(1,:),zs(2,:),zs(3,:), zs(4,:)})


title('Stellar Mass Function (Millenium Data)')
xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$log_{10}N(Mpc^{-3})$$','interpreter','latex')   

