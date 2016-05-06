function [ N ] = calcZ(M)

% The format of M is the following
% (1)Stellar mass, x, y ,z, vx, vy, vz, (8)sdssu, (9)sdssr

% The formate of N is the following
% z , mass, sdssU, sdssR,

% Constants Taken from Millennium, WMAP1 Cosmology
c = 3e8; % m/s
omega_m = 0.25;
omega_l = 0.75;
h = 0.73;
H0 = 100e3 * h; % ms-1 Mpc-1 h
dh = c./H0;

% radial comoving distance
d = sqrt( M(:, 2) .^ 2 + M(:, 3) .^2 + M(:, 4) .^ 2);
vr = sqrt( M(:, 5) .^ 2 + M(:, 6) .^2 + M(:, 7) .^ 2);

% Numerical intergation function
fun = @(z) 1./sqrt(omega_m .* (1 + z) .^ 3 + omega_l);
z = zeros(length(d), 1);

% Generate a superfine lookpup table
tableSize = 10000;
tic
fprintf('Generating Lookup Table with Size: %d\n', tableSize);
zLookup = linspace(0, 6, tableSize);
zLookup = zLookup';
dLookup = zeros(length(zLookup), 1);
for i = 1:length(zLookup)
    dLookup(i) = dh .* integral(fun, 0, zLookup(i));
end
fprintf('Lookup Table Generated\n');
toc;

% Loop up function
tic
for i = 1:length(d)
    [~, I] = min(abs(dLookup - d(i)));
    z(i) = zLookup(I);
    % cosmological redshift
    
end
fprintf('Redshift Lookup Complete\n');
toc

% Velocity descriptions
vr = vr + normrnd(91,50,[length(vr) 1]);
z = (1+z) .* (1+vr./c)-1;

N = [z, M(:, 1), M(:, 8), M(:, 9)];
fprintf('calcZ.m completed \n');
