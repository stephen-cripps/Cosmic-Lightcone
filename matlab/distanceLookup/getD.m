function [d] = getD(z)
%getD 
% Caluclate PHYSICAL distance from observed redshift Z using a lookup table
% z and d are arrays of equal size

accuracy = 6;
lookupTableName = 'zTable.csv';
D = csvread(lookupTableName, 0, 0);
z = round(z .* (10 .^ accuracy));
d = D(z);


end

