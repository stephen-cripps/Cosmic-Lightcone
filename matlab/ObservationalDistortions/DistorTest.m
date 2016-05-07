%% Distor Test 
tic;
% Tao Test Catalogue 
M = csvread('G:\\tao.1598.0.csv', 1, 0);
toc;
% GAMA 
GA = csvread('G:\\GAMA_colour.csv', 1, 0);
toc;


%% Correct the inputs 
% The raw input is in the formate of 
% (1)Mass, (2)RA, (3)Dec, (4)ZCos, (5)ZObs, (6)X, Y, Z, (9)Vx, Vy, Vz, (12)SDSS_U_ABS,
% (13)SDRR_U_apparent, (14)R_ABS, (15)R_Apparent
%


inputM = zeros(length(M), 9);
inputM(:, 1) = M(:, 1);
for i = 2: 7
    inputM(:, i) = M(:, i + 4);
end
inputM(:, 8) = M(:, 12);
inputM(:, 9) = M(:, 14);

%% Distor
tic
N = distor(inputM);
toc

%% Check Distor
% Redshift
zDiff =(M(:, 5) - N(:, 1));
fprintf('Z Error: Max=%f mean=%f\n', max(abs(zDiff)), mean(zDiff));
figure(1)
histogram(zDiff);

% u band 
uDiff = M(:, 12) - N(:, 4);
fprintf('u Error: Max=%f mean=%f\n', max(abs(uDiff)), mean(uDiff));
figure(2)
histogram(uDiff);

% r band 
rDiff = M(:, 14) - N(:, 6);
fprintf('r Error: Max=%f mean=%f\n', max(abs(rDiff)), mean(uDiff));
figure(3)
histogram(rDiff);

%% Plotting Errors 

figure(4)
subplot(1,3,1);
plot(N(:, 3), N(:, 2), '.', 'markers', 1);
ylim([9, 13])
xlabel('Error on Stellar Mass')
ylabel('Stellar Mass')
subplot(1,3,2);
plot(N(:, 5), N(:, 4), '.', 'markers', 1);
% ylim([-24, -14])
% xlim([0, 0.2])
xlabel('Error on U')
ylabel('U Band Magnitude')
subplot(1,3,3);
plot(N(:, 7), N(:, 6), '.', 'markers', 1);
xlim([0, 0.1])
ylim([-24, -14])
xlabel('Error on R')
ylabel('R Band Magnitude')

%% Generate a vr distribution

size = 100000;

n = normrnd(91,50,[1 size]);
histogram(n);

