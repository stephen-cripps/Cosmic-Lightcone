%% 
tic;
M = csvread('D:\\Snapshot\\tao.2000.0.csv', 1, 0);
toc;

%% 
tic;
a = distor(M);
toc;