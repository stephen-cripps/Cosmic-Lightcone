%% Fine Tune Catalogues
% The script take the catalogue from tal and keeps only the the following variables
% Stellar mass, x, y, z, vx, vy, vz, SDSS_U, SDSS_R

tic;
header = 'Total_Stellar_Mass,X,Y,Z,X_Velocity,Y_Velocity,Z_Velocity,SDSS_U, SDSS_R\n';

fid = fopen('test.csv', 'w');
fprintf(fid, 'Total_Stellar_Mass,X,Y,Z,X_Velocity,Y_Velocity,Z_Velocity,SDSS_U, SDSS_R\n');

writeIndex = 2000;

for readIndex = 1485:1529
    toc;
    fprintf('%d / %d \n', readIndex, 1529);
    inputFileName = ['tao.', num2str(readIndex), '.0.csv'];
    fprintf('Input: %s\n', inputFileName);
    M = csvread(inputFileName,1,0);
    toc;
    N = zeros(length(M), 9);
    N(:,1) = M(:,1);    % Stellar Mass
    for i = 2:7         % Position and Velocity
        N(:,i) = M(:,i+1);
    end
    N(:,8) = M(:,9);    % SDSS_U
    N(:,9) = M(:,11);   % SDSS_R
    outputFileName = ['tao.', num2str(writeIndex), '.0.csv'];
    fprintf('Output: %s\n', outputFileName);
    fid = fopen(outputFileName, 'w') ;
    fprintf(fid, header);
    fclose(fid);
    dlmwrite(outputFileName, N, '-append');
    toc;
    writeIndex = writeIndex + 1;
    
end