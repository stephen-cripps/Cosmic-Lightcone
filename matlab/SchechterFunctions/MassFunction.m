clc
close

%Reading in z=1
%  snap1= csvread('tao.1432.0.csv',1,0);
   M1=snap1(:,1);
   
 

%Reading in z=0
%  snap0= csvread('tao.1409.0.csv',1,0);
   M0=snap0(:,1);


%removing zero values
M1=M1(M1~=0);
M0=M0(M0~=0);
%removing all below median
M1=M1(M1>median(M1));
M0=M0(M0>median(M0));


 M1=M1*10^10;
 M0=M0*10^10;
 M1=log10(M1);
 M0=log10(M0);

% Plotting read data functions
[c1,M]=hist(M1,100);
cl1=log10(c1);
cl1(cl1==-inf)=0;
cl1=cl1/sum(cl1);
plot(M,(cl1),'.-')

hold on

[c0,M]=hist(M0,100);
cl0=log10(c0);
cl0(cl0==-inf)=0;
cl0=cl0/sum(cl0);
plot(M,(cl0),'--')

xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$log_{10}N$$','interpreter','latex')
legend('z=1.0779', 'z=0')
title('Normalised Schechter Function: M_* Comparison')