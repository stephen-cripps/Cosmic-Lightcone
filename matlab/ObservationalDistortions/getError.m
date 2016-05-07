function [massErr, uErr, rErr] = getError(mass, u, r)
%UNTITLED2 Input the mass, u band and r band value
% Output the error in mass, u band, r band
% Mass, r and r must be the same length

LT = csvread('ErrorLookup.csv', 0, 0);


massErr = zeros(length(mass), 1);
uErr = massErr;
rErr = massErr;

for i = 1:length(mass)
    % Mass Error
    [~, massIndex] = min(abs(LT(:, 1) - mass(i)));
    massErr(i) = LT(massIndex, 2);
    
    % U band error
    [~, uIndex] = min(abs(LT(:, 3) - u(i)));
    uErr(i) = LT(uIndex, 4);
    
    % R band error
    [~, rIndex] = min(abs(LT(:, 5) - r(i)));
    rErr(i) = LT(rIndex, 6);
%     
%     fprintf('Index: m=%d, u=%d, r=%d\n', massIndex, uIndex, rIndex);
%     fprintf('Mass=%.6f, u=%.6f, r=%.6f\n', mass(i), u(i), r(i));
%     fprintf('Indexed values: Mass=%.6f, u=%.6f, r=%.6f\n', LT(massIndex, 1), LT(massIndex, 3), LT(massIndex, 5))
%     fprintf('Indexed Errors: Mass=%.6f, u=%.6f, r=%.6f\n', LT(massIndex, 2), LT(massIndex, 4), LT(massIndex, 6))
%     
    %break;
end





end

