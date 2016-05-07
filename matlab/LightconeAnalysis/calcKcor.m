function [ kcor ] = calcKcor(z, band, colour)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here


u_ur = [   [0,0,0,0];
    [10.3686,-6.12658,2.58748,-0.299322];
    [-138.069,45.0511,-10.8074,0.95854];
    [540.494,-43.7644,3.84259,0];
    [-1005.28,10.9763,0,0];
    [710.482,0,0,0]];

r_ur = [    [0,0,0,0];
    [3.03458,-1.50775,0.576228,-0.0754155];
    [-47.8362,19.0053,-3.15116,0.286009];
    [154.986,-35.6633,1.09562,0];
    [-188.094,28.1876,0,0];
    [68.9867,0,0,0]];

if band == 'u'
    c = u_ur;
elseif band == 'r'
    c = r_ur;
else
    disp('Unknow band request for k-correction');
end

kcor = zeros(length(z), 1);

for k = 1:length(z)
    
    for i = 1:6
        for j = 1:length(c(i,:))
            kcor(k) = kcor(k) + c(i, j) * z(k) .^ (i-1) * colour(k) .^ (j-1);
        end
    end
end

fprintf('calcKcor.m Complete\n');
end

