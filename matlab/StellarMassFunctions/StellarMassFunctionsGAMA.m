clc
close

data=csvread('E:\Snapshot\GAMA.csv',1,0);


%% PLOT 0
map0=data(:,1)<0.1;
data0=data(map0,:);
M0=data0(:,2);
M0=M0(M0>=9);                            %mass limitation based on our data                        
z0=data0(:,1);

err0=data0(:,3);
err0=mean(err0);

vol0=(4/3)*pi*421.3 ^3*(144/41252.96)  ;    %gamma survey has solid angle of 144deg^2, z=0.2 => r~823.1 mpc, 
                                          %a full sky has solid angle of 41252.96deg^2
[c0,bin]=hist(M0,20);
c0=log10(c0./vol0);                        %produces the data in the form
                                          %used in most observational surveys
%c0=log10(c0);
%c0=c0./vol0;
infmap=c0~=-inf;
c0=c0(c0~=-inf);
bin0=bin(infmap);
%c0=c0/sum(c0);                               %produces normalised data
                                          
plot(bin0,c0,'bx')
hold on
cs=smooth(c0);
cs=smooth(cs);
smoothed0 = plot(bin0,cs,'b-');
error0 = herrorbar(9.5, -6, err0, 'b');
%% PLOT 1
map1=data(:,1)<=0.2 & data(:,1)>=0.1;
data1=data(map1,:);
M1=data1(:,2);
M1=M1(M1>=9);
z1=data1(:,1);

err1=data1(:,3);
err1=mean(err1);

vol1=(4/3)*pi*(144/41252.96)*(823.1^3-421.3 ^3);   
                                                    
[c1 bin1]=hist(M1,20);           %change 20 to bin to get equal bins
c1=log10(c1./vol1);

%c1=log10(c1);
%c1=c1./vol1;
infmap=c1~=-inf;
c1=c1(c1~=-inf);
bin1=bin1(infmap);
%c1=c1/sum(c1);  
 

plot(bin1,c1,'gx')
hold on
cs=smooth(c1);
cs=smooth(cs);
smoothed1 = plot(bin1,cs,'g-');
error1 = herrorbar(9.5, -6.5, err1, 'g');
%% PLOT 2

map2=data(:,1)<=0.3 & data(:,1)>=0.1;
data2=data(map2,:);
M2=data2(:,2);
M2=M2(M2>=9);
z2=data2(:,1);

err2=data2(:,3);
err2=mean(err2);

vol2=(4/3)*pi*(144/41252.96)*(1204.9^3-823.1 ^3);   
                                                    
[c2 bin2]=hist(M2,20);   %change 20 to bin to get equal bins
c2=log10(c2./vol2);

%c1=log10(c1);
%c1=c1./vol1;
infmap=c2~=-inf;
c2=c2(c2~=-inf);
bin2=bin2(infmap);
%c1=c1/sum(c1);  
 

plot(bin2,c2,'rx')
hold on
cs=smooth(c2);
cs=smooth(cs);
smoothed2 = plot(bin2,cs,'r-');
error2 = herrorbar(9.5, -7, err2 ,'r');
%% labels
legend([smoothed0 smoothed1 smoothed2 error0(1,:) error1(1,:) error2(1,:)],{'z<0.1','0.1<z<0.2','0.2<z<0.3', 'Error on log mass @ z=0.1', 'Error on log mass @ z=0.2' ,'Error on log mass @ z=0.3'})


title('Stellar Mass Function (GAMA data)')
xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$log_{10}N(Mpc^{-3}$$)','interpreter','latex')     %include Mpc^{-3} if used vol above

