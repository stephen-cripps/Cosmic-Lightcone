clc
close
%read in data
data=csvread('GAMA/GAMA_colour.csv',1,0);

%Enter columns for the data set and its error
values=data(:,4);
error=data(:,5);

%Any outlier removal required
map=values<-10; 
values=values(map);
error=error(map);


%% GAMA plots
figure(1)
suptitle('mass')
subplot(1,2,1)
histogram(error, 100);
avg=mean(error);
hold on
avgPlot=plot([avg,avg],ylim);
xlabel('$$\Delta mass$$','interpreter','latex')
ylabel('n','interpreter','latex')
set(gca, 'box', 'on')
subplot(1,2,2)
scatter(error, values,'.')
xlabel('$$\Delta mass$$','interpreter','latex')
ylabel('$$mass$$','interpreter','latex')
set(gca, 'box', 'on')

legend(avgPlot,'mean');


%% Generated errors

genError = makeError(error,length(error));

figure(2)
suptitle('M_u (Generated Errors)')
subplot(1,2,1)
histogram(genError, 100);
avg=mean(genError);
hold on
avgPlot=plot([avg,avg],ylim);
xlabel('$$\Delta M_u$$','interpreter','latex')
ylabel('n','interpreter','latex')
set(gca, 'box', 'on')
subplot(1,2,2)
scatter(genError, values,'.')
xlabel('$$\Delta M_u$$','interpreter','latex')
ylabel('$$M_u$$','interpreter','latex')
set(gca, 'box', 'on')

legend(avgPlot,'mean');






       
       
       
       