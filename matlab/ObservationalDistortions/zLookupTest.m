%% Construct a lookup tabel

tic
% Constants Taken from Millennium, WMAP1 Cosmology
c = 3e8; % m/s
omega_m = 0.25;
omega_l = 0.75;
h = 0.73;
H0 = 100e3; % ms-1 Mpc-1 h
dh = c./H0;
fun = @(z) 1./sqrt(omega_m .* (1 + z) .^ 3 + omega_l);

z = linspace(0, 6, 10000);
z = z';
d = zeros(length(z), 1);

for i = 1:length(z)
    d(i) = dh .* integral(fun, 0, z(i));
end

N = [z,d];
toc
value = 10;
diff = abs(d-value);
[~, I] = sort(diff, 'ascend');

fprintf('I: %d, d: %f, z: %f\n', I(1), d(I(1)), z(I(1)));

toc

