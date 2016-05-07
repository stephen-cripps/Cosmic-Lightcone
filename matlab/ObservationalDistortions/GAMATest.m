%% Looking more into GAMA Errors 
tic
GA = csvread('G:\\GAMA_colour.csv', 1, 0);
toc

%% Limitation 
% Mass 
massIndex = find(GA(:, 2) > 9);
M = GA(massIndex, :);
% R band 
rIndex = find(M(:, 6) > -24);
M = M(rIndex, :);
% rErr min
index = find(M(:, 7) > 0.01);
M = M(index, :);
% uErr Min
index = find(M(:, 5) > 0.02);
M = M(index, :);
%% Plots 
figure(1)
subplot(2,3,1);
plot(M(:, 3), M(:, 2), '.', 'markers', 1);
ylim([9, 13])
xlabel('Error on Stellar Mass')
ylabel('Stellar Mass')
subplot(2,3,2);
plot(M(:, 5), M(:, 4), '.', 'markers', 1);
ylim([-24, -14])
xlim([0, 0.2])
xlabel('Error on U')
ylabel('U Band Magnitude')
subplot(2,3,3);
plot(M(:, 7), M(:, 6), '.', 'markers', 1);
xlim([0, 0.1])
ylim([-24, -14])
xlabel('Error on R')
ylabel('R Band Magnitude')

%% Error Generation 

dlmwrite('ErrorLookup.csv', M(:, 2:7),'precision','%.6f');

%%
[massErr, uErr, rErr] = getError(M(:,2), M(:,4), M(:,6));
subplot(2,3,4);
plot(massErr, M(:, 2), '.', 'markers', 1);
% ylim([9, 13])
xlabel('Error on Stellar Mass')
ylabel('Stellar Mass')
subplot(2,3,5);
plot(uErr, M(:, 4), '.', 'markers', 1);
% ylim([-24, -14])
% xlim([0, 0.2])
xlabel('Error on U')
ylabel('U Band Magnitude')
subplot(2,3,6);
plot(rErr, M(:, 6), '.', 'markers', 1);
% xlim([0, 0.1])
% ylim([-24, -14])
xlabel('Error on R')
ylabel('R Band Magnitude')


%% Generating Random mass values 

figure(2)
histogram(M(:, 2))

figure(3)
n = normrnd(10,0.5,[1 60000]);
n = n(n>9);
histogram(n);

[massErr, ~, ~] = getError(n, zeros(1,60000),zeros(1,60000));
figure(4)
plot(massErr, n, '.', 'markers', 1);



