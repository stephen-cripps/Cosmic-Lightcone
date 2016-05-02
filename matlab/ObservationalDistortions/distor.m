function [ N ] = distor( M )
%distor
% This function takes a lightcone catalogue M and apply observational
% distoration and return with te new catalouge N

% Constants Taken from Millennium, WMAP1 Cosmology
c = 3e8; % m/s
omega_m = 0.25;
omega_l = 0.75;
h = 0.73;
H0 = 100e3; % ms-1 Mpc-1 h
dh = c./H0;

% The formate of M is the following
% Stellar mass, x, y ,z, vx, vy, vz, sdssu, sdssr

% The formate of N is the following
% observed redshift, mass, empty, sdssU, empty, sdssR, empty

% radial comoving distance
d = sqrt( M(:, 2) .^ 2 + M(:, 3) .^2 + M(:, 4) .^ 2);
vr = sqrt( M(:, 5) .^ 2 + M(:, 6) .^2 + M(:, 7) .^ 2);

%% Caluclats the observed redshfit
% Numerical intergation function
fun = @(z) 1./sqrt(omega_m .* (1 + z) .^ 3 + omega_l);
z = zeros(length(d), 1);

% Generate a superfine lookpup table
tableSize = 10000;
tic
fprintf('Generating Loopup Table with Size: %d\n', tableSize);
zLookup = linspace(0, 6, tableSize);
zLookup = zLookup';
dLookup = zeros(length(zLookup), 1);
for i = 1:length(zLookup)
    dLookup(i) = dh .* integral(fun, 0, zLookup(i));
end
fprintf('Loopup Table Generated\n');
toc;

% Loop up function
tic
for i = 1:length(d)
    [~, I] = min(abs(dLookup - d(i)));
    z(i) = zLookup(I);
end
fprintf('Redshift Lookup Complete\n');
toc


%% Magnitude Distoration
apparent = @(Mag, d) Mag - 5 .* (1 - log10(d*1e6));

u = apparent(M(:, 8), d);
r = apparent(M(:, 9), d);


%% Combine everything together 
empty = zeros(length(M), 1);

N = [z, M(:, 1), empty, u, empty, r, empty];

end

