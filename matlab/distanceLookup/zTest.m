clear;

%% Generate the Lookup Table for 
accuracy = 6;
range = 0.5;
z = 0: 1/(10 .^ accuracy) : range;
d = zeros(1, length(z));

%% 
% Constants Taken from Millennium, WMAP1 Cosmology
c = 3e8; % m/s
omega_m = 0.25;
omega_l = 0.75;
h = 0.73;
H0 = 100e3; % ms-1 Mpc-1 h
H0 = H0 .* h;
dh = c./H0;
fun = @(z) dh./sqrt(omega_m .* (1 + z) .^ 3 + omega_l);

tic
for i = 1:length(z)
    d(i) = integral(fun, 0, z(i)) ./ h;
    % fprintf('Estimate Time: %f\n', length(z) * toc / i);
end
%% 
csvwrite('zTable.csv', d);
toc




%%
size = 10000;
% Generate random test points
zRange = 0.5;
z = zRange .* rand(1, size);

%% 
d = zeros(1, length(z));
tic
for i = 1:length(z)
    d(i) = integral(fun, 0, z(i)) ./ h;
end
fprintf('Intergal time: %f\n', toc);


tic
d2 = getD(z);
fprintf('Lookup time: %f\n', toc);

fprintf('Maximum Difference: %f\n', max(abs(d' - d2)));
%% plot
figure(1)
plot(d2, d, '.');
axis equal
xlabel('Lookup Value')
ylabel('Integral Value')





