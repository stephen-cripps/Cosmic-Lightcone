

% Taken from Millennium, WMAP1 Cosmology 
c = 3e8; % m/s 
omega_m = 0.25;
omega_l = 0.75;
h = 0.73;
H0 = 100e3; % ms-1 Mpc-1 h 
dh = c./H0;
loopSize = 25;


realZ = 0.129889080318;

fun = @(z) 1./sqrt(omega_m .* (1 + z) .^ 3 + omega_l);
d =  dh .* integral(fun, 0, realZ);

zMin = 0;
zMax = 6;
for i = 1:loopSize
    zTry = (zMin + zMax) /2;
    dTry = dh .* integral(fun, 0, zTry);
    fprintf('%d: zTry: %f, dTry: %f\n', i, zTry, dTry);
    
    if dTry > d
        zMax = zTry;
    elseif dTry < d
        zMin = zTry;
    end
end

zTry