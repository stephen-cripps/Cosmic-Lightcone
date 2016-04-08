clc 
close



i=1;


for fileNo = [1, 2,  3,  5]

%Read in files
fileName=num2str(fileNo);
fullName=['C:\Users\user\Documents\LightconeMatlabBS\SDSS\SDSSPassive0',fileName,'.csv']; %Change this to SDSS Forming to get the forming port
snapshot=csvread(fullName,2,0);

%Select Mass and apply limitation to ignore poor mas resolutions at higer
%redshifts
M=snapshot(:,2);
M=M(M>10);

%Create normalised histogram, ignore infinite points to avoid issues in sum
[c,M]=hist(M,20);
c=log10(c);
infmap=c~=-inf;
c=c(infmap);
M=M(infmap);
c=c/sum(c);

% Set colour depending on loop
colour=[0 0 0];
colour(:,i)=1;

%Plot points
plot(M,(c),'color',colour,'linestyle','none','marker','x')
hold on
%plot smoothed line
cs=smooth(c);
smoothed(i)=plot(M,cs,'color',colour);

%record redshift for legend
z=fileNo/10;
zl(i,:) =sprintf('%0.1f',z-0.1);
zu(i,:) =sprintf('%0.1f',z);
zsfull(i,:) =strcat(zl(i,:),'<z<', zu(i,:));
i=i+1;
end

%plot
axis([10 13.5 0.01 0.1])

legend([smoothed(:,1) smoothed(:,2) smoothed(:,3) smoothed(:,4)],{zsfull(1,:),zsfull(2,:),zsfull(3,:), zsfull(4,:)})


title('Stellar Mass Function for SDSS (Passive port)')
xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$log_{10}N$$','interpreter','latex')

