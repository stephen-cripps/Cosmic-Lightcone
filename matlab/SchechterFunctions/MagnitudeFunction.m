clc
close

%Reading in z=1
%  M1= csvread('tao.1432.0.csv',1,0);
%  M1=M1(:,10);
%  M1=M1(M1~=100);
% 

%Reading in z=0
%  M0= csvread('tao.1409.0.csv',1,0);
%  M0=M0(:,10);
%  M0=M0(M0~=100);

%generating perfect schecter fn
% x= linspace(0.01,20,10000);
% X=15;
% norm = 0.5;
% a= -1e-10;

% phi=norm.*(x./X).^a.*exp(-5e-1*x./X);
% plot(log10(x)*(3.8)+23.5,log10(phi)+0.322)
% axis([0,30,0,0.05])
% hold on
 
%Plotting read data functions
[c1,MB]=hist(M1,100);
cl1=log10(c1);
cl1(cl1==-inf)=0;
cl1=cl1/sum(cl1);
plot(-MB,(cl1),'.')

hold on

[c0,MB]=hist(M0,100);
cl0=log10(c0);
cl0(cl0==-inf)=0;
cl0=cl0/sum(cl0);
plot(-MB,(cl0),'x')

xlabel('-M_B')
ylabel('log_{10} N')
legend('z=1.0779', 'z=0')
title('Normalised Schechter Function: M_B Comparison')