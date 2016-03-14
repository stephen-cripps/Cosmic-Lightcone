clear;
clc;
close;

%
z = csvread('redshift.txt');
x = 31:-1:1;
% Working in SI Units for now bro
c = 3e8;
h = 0.73;
a0 = 1;
H0 = 100*1000 *h; % H0 is 100 km h s^-1 Mpc^-1

f = @(z) z.*(1+z).*c./(a0.*H0);

r = f(z);

%subplot(1,2,1)
plot(z,r);
xlabel('Redshift Z')
ylabel('Comoving Radius r (Mpc)')

%subplot(1,2,2)
% plot(x,r);
% xlabel('Snapshot Number')

for i = 1:31
    fprintf('Snapshot: %d z: %f, r(Mpc): %f \n', x(i)-1, z(i), r(i));
end

figure(2)
boxSize = 500;
plot(z,ceil(r./boxSize), '-');




