clc
clear 

data=csvread('OUTPUT\MOCK(1689.2)(45)(45)(7.563).csv',1,0);
% (1)Stellar mass, (2)x, (3)y ,(4)z, (5)vx, (6)vy, (7)vz, (8)sdssu, (9)sdssr
solidAngle=179.94; 

%% Observational effects

%Calculating Redshift, zData format: z(1), mass(2), sdssU(3), sdssR(4),
zData = calcZ(data);

%K-correct and get apparant magnitudes
[uApp, rApp] = calcApparent(zData(:,1), zData(:,3), zData(:,4));

%Applying magnitude limits
magLim= rApp < 17;
limData = zData(magLim,:);

%Finding observed redshift + errors, cone format:% z(1), logMass(2), logMassErr(3), u(4), uErr(5), r(6), rErr(7)];
cone = distor(limData);

%Applying errors to measured values 


mass= cone(:,2) + normrnd(0,(cone(:,3)./2),[length(cone(:,2)) 1]);
u= cone(:,4) + normrnd(0,(cone(:,5)./2),[length(cone(:,4)) 1]);
r= cone(:,6) + normrnd(0,(cone(:,7)./2),[length(cone(:,6)) 1]);

%% Stellar Mass Functions
figure(1)
%preallocate lower limit redshifts to plot
z=[0 0.1 0.2 0.4];
sz=size(z);
%allocate step in redshift
stepsize=0.1;

% Cosmologys for distance 

c = 3e8; % m/s 
omega_m = 0.25;
omega_l = 0.75;
h = 0.73;
H0 = 100e3*h; % ms-1 Mpc-1 h 

%function for redshift distance
func = @(z) c ./(H0 .* sqrt(omega_m .* (1+z).^3 + omega_l));

%preallocation of arrays

bins = linspace(9, 13, 50);
for i=1:sz(2)
    %Find masses and redshifts which belong to galaxies within the redshift limits
    map=cone(:,1)<=z(:,i)+stepsize & cone(:,1)>=z(:,i) & mass>=9 & mass <= 13;
    M=mass(map);
    
    %finding the volume of the current section
    rmin= integral(func, 0, z(i));
    rmax=integral(func, 0, z(i)+0.1);
    stepVol=(solidAngle/41252.96)*(4/3)*pi*(rmax^3-rmin^3);
    
    %Create normalised histogram, ignore infinite points to avoid issues in sum
    [c,bin]=hist(M,bins);
    c=log10(c/stepVol);
    infmap=c~=-inf;
    c=c(infmap);
    bin=bin(infmap);
    
    %Plot points
    ax = gca;
    ax.ColorOrderIndex = i;
    plot(bin,c,'linestyle','none','marker','x')
    hold all
    %plot smoothed line
    ax = gca;
    ax.ColorOrderIndex = i; %to make colours consistent though loop 
    cs=smooth(c);
    smoothed(:,i)=plot(bin,cs);
    
     %Store redshifts for legend
    zl(i,:) =sprintf('%0.1f',z(:,i));
    zu(i,:) =sprintf('%0.1f',z(:,i)+stepsize);
    zsfull(i,:) =strcat(zl(i,:),'<z<', zu(i,:));
end

legend([smoothed(:,1) smoothed(:,2) smoothed(:,3) smoothed(:,4)], {zsfull(1,:),zsfull(2,:),zsfull(3,:),zsfull(4,:)})

axis([10 12 -7 -2])
xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$log_{10}N(Mpc^{-3})$$','interpreter','latex')

%% Colour Magnitude Diagrams
figure(2)
for i=1:sz(2)
    subplot(1, sz(2), i)
    cMap=cone(:,1)<=z(:,i)+stepsize & cone(:,1)>=z(:,i);
    %apply map to data
    cutu=u(cMap);
    cutr=r(cMap);

    %generate values for plotting
    difference=cutu-cutr;
    x=cutr-5*log10(h);
    
    dscatter(x,difference,'BINS',[1000 1000])
    axis([-25 -15 0 3])
    ylabel('$$M_u-M_r$$','interpreter','latex')
    xlabel('$$M_r-5logh$$','interpreter','latex')
end


%% output cones to use for cosmic variance ect

csvwrite('distortedLightcones/LC1.csv',cone);












