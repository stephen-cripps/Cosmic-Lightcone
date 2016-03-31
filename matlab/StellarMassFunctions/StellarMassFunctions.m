clc 
close



i=1;
redshift=csvread('E:\Snapshot\redshiftStep.txt');
redshift=fliplr((redshift(7:31,:))');

for fileNo = [1409, 1424, 1433]


fileName=num2str(fileNo);
fullName=['E:\Snapshot\tao.',fileName,'.0.csv'];
snapshot=csvread(fullName,1,0);

M=snapshot(:,1)*10^10;
M=M(M~=0);
M=log10(M);

[c,M]=hist(M,100);
c=log10(c);
c(c==-inf)=0;
c=c/sum(c);
c(:,100)=0;
colour=[0 0 0];
colour(:,i)=1;
plot(M,(c),'color',colour,'linestyle','x')
hold on
cs=smooth(c);
cs=smooth(cs);
smoothed(i)=plot(M,cs,'color',colour);
z= redshift(:,fileNo-1408);
zs(i,:)= ['z=' sprintf('%.5f', z)];

i=i+1;
end


legend([smoothed(:,1) smoothed(:,2) smoothed(:,3)],{zs(1,:),zs(2,:),zs(3,:)})


title('Stellar Mass Function')
xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('$$log_{10}N$$','interpreter','latex')

