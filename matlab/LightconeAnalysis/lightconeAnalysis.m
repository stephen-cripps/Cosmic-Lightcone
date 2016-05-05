clc
close
data=csvread('OUTPUT\MOCK(1689.2)(30)(30)(7.563).csv',1,0);
% (1)Stellar mass, (2)x, (3)y ,(4)z, (5)vx, (6)vy, (7)vz, (8)sdssu, (9)sdssr
solidAngle=179.94; 

%% Observational effects

%Applying magnitude limits

apparent = @(Mag, d) Mag - 5 .* (1 - log10(d*1e6));
d=sqrt(data(:, 2).^2+data(:, 3).^2+data(:, 4).^2);
appr = apparent(data(:, 9), d);

magLim= appr < 19;
limData = data(magLim,:);

%Finding observed redshift + errors
cone = distor(limData);

%Applying errors to measured values 
% z(1), logMass(2), logMassErr(3), u(4), uErr(5), r(6), rErr(7)];

mass= cone(:,2) + normrnd(0,(cone(:,3)./2),[length(cone(:,2)) 1]);
u= cone(:,4) + normrnd(0,(cone(:,5)./2),[length(cone(:,4)) 1]);
r= cone(:,6) + normrnd(0,(cone(:,7)./2),[length(cone(:,6)) 1]);

%% Stellar Mass Functions

%preallocate upper limit redshifts to plot
z=0:0.1:0.2;
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


for i=1:sz(2)
    %Find masses and redshifts which belong to galaxies within the redshift limits
    map=cone(:,1)<=z(:,i)+stepsize & cone(:,1)>=z(:,i);
    M=mass(map);
    
    %finding the volume of the current section
    rmin= integral(func, 0, z(i));
    rmax=integral(func, 0, z(i)+0.1);
    stepVol=(solidAngle/41252.96)*(4/3)*pi*(rmax^3-rmin^3);
    
    %Create normalised histogram, ignore infinite points to avoid issues in sum
    [c,bin]=hist(M,20);
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
    smoothed=plot(bin,cs);
    
     %Store redshifts for legend
    zl(i,:) =sprintf('%0.1f',z(:,i));
    zu(i,:) =sprintf('%0.1f',z(:,i)+stepsize);
    zsfull(i,:) =strcat(zl(i,:),'<z<', zu(i,:));
end

legend([smoothed(1) smoothed(2) smoothed(3)], {zsfull(1,:),zsfull(2,:),zsfull(3,:)})

axis([10 12 -7 -3.5])
xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$log_{10}N(Mpc^{-3})$$','interpreter','latex')
















