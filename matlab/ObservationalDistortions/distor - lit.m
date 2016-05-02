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
loop = 10; % to 6 decimied place
% Numerical intergation function
fun = @(z) 1./sqrt(omega_m .* (1 + z) .^ 3 + omega_l);
z = zeros(length(d), 1);

for index = 1:length(d)
    tic
    zMin = 0;
    zMax = 6;
    for i = 1:loop
        zTry = (zMin + zMax) / 2;
        dTry = dh .* integral(fun, 0, zTry);
        if dTry > d
            zMax = zTry;
        elseif dTry < d
            zMin = zTry;
        end
    end
    
    % Cosmological Z;
    cosZ = (zMax + zMin) / 2;
    
    zpec = vr(i) ./ c;
    z(i) = (1+cosZ) .* (1+zpec) -1;
    % The above is the observed redshfit  
    fprintf('Index is : %d\n', index);
    toc
end




end

