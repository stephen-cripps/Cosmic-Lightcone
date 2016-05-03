%% Distor Test 
tic;
M = csvread('tao.1598.0.csv', 1, 0);
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
zDiff = abs(M(:, 5) - N(:, 1));
fprintf('Z Error: Max=%f mean=%f\n', max(zDiff), mean(zDiff));

% u band 
uDiff = abs(M(:, 13) - N(:, 4));
fprintf('u Error: Max=%f mean=%f\n', max(uDiff), mean(uDiff));

% r band 
rDiff = abs(M(:, 15) - N(:, 6));
fprintf('r Error: Max=%f mean=%f\n', max(rDiff), mean(uDiff));

