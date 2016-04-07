clear all;
clc;

fprintf('Loading the SnapShot . . . ');
tic
S = csvread('E:\\NewSnapshotFull\\tao.1409.0.csv', 1, 0, [1 0 17000000 0]); % inital rc, final rc 
toc

%% 
figureSize = [100, 100, 960, 380];
%% 10 Mpc
% 10Mpc Number
f10 = figure(1);
set(f10, 'Position', figureSize);
subplot(1,2,1)
n10 = csvread('10MpcGalaxyNumberGrid.csv');
n10 = n10(:,1);
histogram(n10, 'Normalization', 'probability');
xlim([0 800])
xlabel('No. Galaxies per 10Mpc Box');
ylabel('Fraction')

% 10Mpc Mass
m10 = csvread('10MpcMassGrid.csv');
subplot(1,2,2)
m10 = m10(:,1);
histogram(m10, 'Normalization', 'probability');
xlim([0 300])
xlabel('Total Mass per 10Mpc Box (10^{10} Solar Mass)');
ylabel('Fraction')

%% Number 20Mpc Box
f20 = figure(2);
set(f20, 'Position', figureSize);
subplot(1,2,1)
n20 = csvread('20MpcGalaxyNumberGrid.csv');
n20 = n20(:,1);
histogram(n20, 'Normalization', 'probability');
xlim([0 4000])
xlabel('No. Galaxies per 20Mpc Box');
ylabel('Fraction')

% Total 10Mpc Box
m20 = csvread('20MpcMassGrid.csv');
subplot(1,2,2)
m20 = m20(:,1);
histogram(m20, 'Normalization', 'probability');
xlim([0 2000])
xlabel('Total Mass per 20Mpc Box (10^{10} Solar Mass)');
ylabel('Fraction')

%% Total Mass Distribution
figure(3)
histogram(S(:, 1), 'Normalization', 'probability');
xlim([0 0.5])
xlabel('Galaxy Mass (10^{10} Solar mass)');
ylabel('Fraction');

%% B-Band Distribution
figure(4)
bm = S(:,10);
bm = bm(bm~=100);
histogram(bm, 300, 'Normalization', 'probability');
xlim([-25 -5])
xlabel('B-band Absolute Magnitude');
ylabel('Fraction');
