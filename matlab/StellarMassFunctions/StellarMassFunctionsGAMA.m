clc
close
%read in data
data=csvread('GAMA.csv',1,0);
%preallocate upper limit redshifts to plot
z=[0.1 0.2 0.3];
mass=data(:,2);

for i=1:3
%Find masses and redshifts which belong to galaxies within the redshift limits    
map=data(:,1)<=z(:,i) & data(:,1)>=z(:,i)-0.1 ;

M=mass(map);
M=M(M>=10);                            %mass limitation to help avoid low resolution     


%finding the volume of the current section
stepz = z(i);
rmin=(stepz-0.1)*((stepz-0.1)+1)*3e8/(73e3);
rmax=(stepz)*((stepz)+1)*3e8/(73e3);
stepVol=(286/41252.96)*(4/3)*pi*(rmax^3-rmin^3);

%Create normalised histogram, ignore infinite points to avoid issues in sum
[c,bin]=hist(M,20);
c=log10(c/stepVol);
infmap=c~=-inf;
c=c(infmap);
bin=bin(infmap);
%c=c/sum(c);                            
                                          
% Set colour depending on loop
colour=[0 0 0];
colour(:,i)=1;

%Plot points
plot(bin,c,'color',colour,'linestyle','none','marker','x')
hold on
%plot smoothed line
cs=smooth(c);
smoothed(i)=plot(bin,cs,'color',colour);

zl(i,:) =sprintf('%0.1f',z(:,i)-0.1);
zu(i,:) =sprintf('%0.1f',z(:,i));
zsfull(i,:) =strcat(zl(i,:),'<z<', zu(i,:));
end

 legend([smoothed(:,1) smoothed(:,2) smoothed(:,3)],{zsfull(1,:),zsfull(2,:),zsfull(3,:)})
 

 title('Stellar Mass Function (GAMA data)')
 xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
 ylabel('$$log_{10}N(Mpc^{-3})$$','interpreter','latex')     %include Mpc^{-3} if used vol above

