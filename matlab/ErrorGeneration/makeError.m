function [ generatedError ] = makeError( error, request )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

% shuffle 
index = randperm(request);
index = mod(index,length(error)) +1;
generatedError = error(index);

end

