clc
close

%Reading in and plotting z=0 data
%  snap0= csvread('tao.1409.0.csv',1,0);
   M0=snap0(:,1);
   M0=M0(M0~=0);
   M0=M0*10^10;
   M0=log10(M0);
   M0=M0(M0>7);
   M0=M0(M0<12);
 
h=0.73;
vol=(500*h)^3;
   
[c0,M]=hist(M0,obs0(:,1));
cl0=log10((c0./vol));
cl0(cl0==-inf)=0;
plot(M,(cl0),'--')

hold on 
%Plotting Observational Data
%obs0=csvread('SMF_Z_0.csv',1,0);

errorbar(obs0(:,1),obs0(:,2),obs0(:,3))

xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$\phi(Mpc^{-3}dex^{-1}$$','interpreter','latex')
legend('Sage/Millenium Data', 'Observational data')
title('Observational vs Simulated Mass Function Comparison: z=0')

% %% z=1
% %  snap0= csvread('tao.1409.0.csv',1,0);
%   M1=snap1(:,1);
%   M1=M1(M1~=0);
%   M1=M1*10^10;
%   M1=log10(M1);
%   M1=M1(M0>7);
%   M1=M1(M0<12);
%    
%    h=0.73;
% vol=(500*h)^3;
% 
% [c1,M]=hist(M0,obs0(:,1));
% cl1=log10((c1./vol));
% cl1(cl1==-inf)=0;
% plot(M,(cl1),'--')
% xlim([8 11.5])
% hold on 
% %Plotting Observational Data
% obs1=csvread('SMF_Z_2.csv',1,0);
% 
% errorbar(obs0(:,1),obs0(:,2),obs0(:,3))




