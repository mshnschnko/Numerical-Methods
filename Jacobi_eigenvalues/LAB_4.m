n = 10;
count = 10;
fileN = fopen('N.txt', 'w');
fprintf(fileN, '%i %i', n, count);
fclose(fileN);
%arrForSeparability = linspace(5, 200, count)
file1 = fopen('matrix.csv', 'w');
fclose(file1);
sep_value = 0.96;
arr_sep = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.99];
% arr_sep = [0.1, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9];
file1 = fopen('matrix.csv', 'a');
new_sep_value = sep_value;
filesep = fopen('sepValue.csv', 'w');
fclose(filesep);
filesep = fopen('sepValue.csv', 'a');
fprintf(filesep, '%f\n', arr_sep);
D = zeros(n, n);
for i=1:count
    %D = diag(linspace(1, 10, n));
     for j=1:n-1
         if j == 1
             D(j,j) = 1; %diag(linspace(1, arrForSeparability(i), n));
             D(j+1, j+1) = D(j,j)*(arr_sep(i)); %(new_sep_value);
         else
             D(j+1, j+1) = D(j,j)*(arr_sep(i)); %(new_sep_value);
         end
     end
    [Q, R] = qr(rand(n)*20);
    A = Q*D*Q';
    for j=1:n
        AR = A(j,:);
        fprintf(file1, '%.17f;', AR);
        fprintf(file1, '\n');
    end
    fprintf(file1, '\n');
%     fprintf(filesep, '%.17f\n', new_sep_value);
%     new_sep_value = sep_value/(i+1);

    eig(A);
end
fclose(file1);

%исследование на устойчивость через возмущение=============================

fileOutrage = fopen('Outrage.csv', 'w');
fclose(fileOutrage);
fileOutrage = fopen('Outrage.csv', 'a');

fileEig = fopen('EigFromMatlab.csv', 'w');
fclose(fileEig);
fileEig = fopen('EigFromMatlab.csv', 'a');

delta = [0.00001, 0.0001, 0.001, 0.01, 0.1, 1];
delta_len = length(delta);

D1 = diag(linspace(1, n, n));
[Q, R] = qr(rand(n)*20);
Achoosen = Q*D1*Q';
eig(Achoosen);

% fprintf(fileEig, "%.17f;", eig(Achoosen));

EigenVectorsMatlab = fopen("EigenVectorsMatlab.csv", "w");
fclose(EigenVectorsMatlab);
EigenVectorsMatlab = fopen("EigenVectorsMatlab.csv", "a");

[V,L] = eig(Achoosen);
for i=1:n
    fprintf(fileEig, "%.17f;", L(i,i));
end
fclose(fileEig);
for i=1:n
    VR = V(i,:);
    fprintf(EigenVectorsMatlab, '%.17f;', VR);
    fprintf(EigenVectorsMatlab, '\n');
end

for i=1:delta_len
    A1 = Achoosen + delta(i);%*rand(n, n);
    for j=1:n
        AR = A1(j,:);
        fprintf(fileOutrage, '%.17f;', AR);
        fprintf(fileOutrage, '\n');
    end
    fprintf(fileOutrage, '\n');
end

fclose(fileOutrage);


%замер времени=============================================================

% fileTime = fopen('matrixTime.csv', 'w');
% fclose(fileTime);
% 
% fileTime = fopen('matrixTime.csv', 'a');
% 
% for n=10:5:100
%     D = diag(linspace(1, n, n));
%     [Q, R] = qr(rand(n)*20);
%     A = Q*D*Q'; 
%     for j=1:n
%         AR = A(j,:);
%         fprintf(fileTime, '%.17f;', AR);
%         fprintf(fileTime, '\n');
%     end
%     fprintf(fileTime, '\n');
% end
% fclose(fileTime);