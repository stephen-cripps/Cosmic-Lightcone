%% Variance analysis
clc
clear

cone=[];
for i=1
    filename= strcat('distortedLightcones/LC', sprintf('%d',i),'.csv') ;
    current=csvread(filename);
    cone=[cone; current];
end

solidAngle=179.94; 

%% Reduce Sample by a factor of 10
sizeR= size(cone,1);
N = sizeR/10 ; %Select 1/10 of the data set
R = zeros(sizeR,1);  % set all to zero
ix = randperm(numel(R)); % randomize the linear indices
ix = ix(1:N); % select the first N indicies 
R(ix) = 1; % set the corresponding positions to 1
cut = R > 0.5; 
cone= cone(cut,:);

%% Stellar mass functions

mass=cone(:,2);
figure(1)
%preallocate lower limit redshifts to plot
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

legend([smoothed(:,1) smoothed(:,2) smoothed(:,3)], {zsfull(1,:),zsfull(2,:),zsfull(3,:)})

axis([10 12 -7 -2])
xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$log_{10}N(Mpc^{-3})$$','interpreter','latex')

%% Colour Magnitude Diagrams
figure(2)
u=cone(:,4);
r=cone(:,6);
for i=1:sz(2)
    subplot(1, sz(2), i)
    cMap=cone(:,1)<=z(:,i)+stepsize & cone(:,1)>=z(:,i);
    %apply map to data
    cutu=u(cMap);
    cutr=r(cMap);

    %generate values for plotting
    difference=cutu-cutr;
    x=cutr-5*log10(h);
    
    %Colour map is relative => no need for corrections here (i think)
    dscatter(x,difference,'BINS',[1000 1000])
    axis([-25 -15 0 3])
    ylabel('$$M_u-M_r$$','interpreter','latex')
    xlabel('$$M_r-5logh$$','interpreter','latex')
end

