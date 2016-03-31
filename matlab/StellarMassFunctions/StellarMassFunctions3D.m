clc
close



% 
% z=csvread('E:\Snapshot\redshiftStep.txt');
% z=fliplr((z(7:31,:))');
% 
% for fileNo = 1409:1433
%     i=fileNo-1408;
%     
%     fileName=num2str(fileNo);
%     fullName=['E:\Snapshot\tao.',fileName,'.0.csv'];
%     snapshot=csvread(fullName,1,0);
%     
%     M=snapshot(:,1)*10^10;
%     M=M(M~=0);
%     M=log10(M);
%     
%     
%         [c,x(i,:)]=hist(M,100);
%         c=log10(c);
%         c(c==-inf)=0;
%         c=c/sum(c);
%         c(:,100)=0;
%         c=smooth(c);
%         c=smooth(c);
%         count(i,:)=c;
%     
%          
%     
%     disp(i)
% end



surf(x(25,:),z,count)



title('Stellar Mass Function')
xlabel('$$log_{10}M_*[M_{\odot}]$$','interpreter','latex')
ylabel('z')
zlabel('$$log_{10}N$$','interpreter','latex')

