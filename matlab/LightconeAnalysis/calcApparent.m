function [uApp, rApp] = calcApparent(z, uAbs, rAbs)
%Caluclates the apparent magnitues with k correction 

uKcor = calcKcor(z, 'u', uAbs - rAbs);
rKcor = calcKcor(z, 'r', uAbs - rAbs);


% Improved d from observed redshift 
% Constants Taken from Millennium, WMAP1 Cosmology
c = 3e8; % m/s
omega_m = 0.25;
omega_l = 0.75;
h = 0.73;
H0 = 100e3; % ms-1 Mpc-1 h
H0 = H0 .* h;
dh = c./H0;

fun = @(z) dh./sqrt(omega_m .* (1 + z) .^ 3 + omega_l);
d = zeros(length(z), 1);
tic
for i = 1:length(z)
    d(i) = integral(fun, 0, z(i));
    if rem(i,10000) == 0
    toc
    disp(i)
    end
end
d = d ./ h;



app = @(abs, d, kcor) abs + 5 .* (log10(d .* 1e6) -1 ) + kcor;

uApp = app(uAbs, d, uKcor);
rApp = app(rAbs, d, rKcor);

fprintf('calacApparant.m Complete\n');
end

