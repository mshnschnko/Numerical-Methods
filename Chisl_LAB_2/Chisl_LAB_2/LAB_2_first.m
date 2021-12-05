n = 10;

cond_val = [10, 10^2, 10^3, 10^4, 10^5, 10^6, 10^7, 10^8, 10^9, 10^(10)];

X = randn(n, 1) * 10;

fileX = fopen('roots.csv', 'w');
fprintf(fileX, '%.17f;', X);
fclose(fileX);

cond_val_len = length(cond_val);

file1 = fopen('csvmatrix.csv', 'w');
fclose(file1);

file2 = fopen('freekoef.csv', 'w');
fclose(file2);

file1 = fopen('csvmatrix.csv', 'a');

file2 = fopen('freekoef.csv', 'a');
fileCompare = fopen('matrixforcompare.csv', 'w');
fclose(fileCompare);
fileBCompare = fopen('matrixBforcompare.csv', 'w');
fclose(fileBCompare);
fileCompare = fopen('matrixforcompare.csv', 'a');
fileBCompare = fopen('matrixBforcompare.csv', 'a');
%%%%%%db = 0.01*rand(n, 1)
summa = 0;
for i = 1:cond_val_len
    D = diag(linspace(1, cond_val(i), n));
    [Q, R] = qr(rand(n)*20);
    A = Q*D*Q';
    AH = hess(A);
    cond(AH);    
    B = AH * X;
    fprintf(file2, '%.17f;', B);
    for j=1:n
        AR = AH(j,:);
        fprintf(file1, '%.17f;', AR);
        fprintf(file1, '\n');
    end
    if i == 1
        Achoosen = AH;
        Bchoosen = B;
    end


    fprintf(file1, '\n');
    fprintf(file2, '\n');
    fprintf(file2, '\n');
end

fclose(file1);
fclose(file2);


delta = [0.00001, 0.0001, 0.001, 0.01, 0.1, 1];
delta_len = length(delta);

filen = fopen('NNN.txt', 'w');
fprintf(filen, '%i %i %i', n, cond_val_len, delta_len);
fclose(filen);

%db = rand(1, n).*delta
fileOutrageB = fopen('OutrageB.csv', 'w');
fclose(fileOutrageB);
fileOutrageA = fopen('OutrageA.csv', 'w');
fclose(fileOutrageA);

fileOutrageB = fopen('OutrageB.csv', 'a');
fileOutrageA = fopen('OutrageA.csv', 'a');

for i = 1:delta_len
    A = Achoosen; %+ delta(i)*Achoosen;
    B = Bchoosen + delta(i)*rand(n, 1); %Bchoosen;
    fprintf(fileOutrageB, '%.17f;', B);
    
    for j=1:n
        AR = A(j,:);
        fprintf(fileOutrageA, '%.17f;', AR);
        fprintf(fileOutrageA, '\n');
    end
    fprintf(fileOutrageA, '\n');
    fprintf(fileOutrageB, '\n');
    fprintf(fileOutrageB, '\n');
end

%for d = 1:delta_len
 %   dB = delta(d)*rand(n,1);
  %  A = Achoosen; %+ delta(i)*Achoosen;
   % for j=1:n
    %    AR = A(j,:);
     %   fprintf(fileOutrageA, '%.17f;', AR);
      %  fprintf(fileOutrageA, '\n');
    %end
    %for xi = 1:n
     %   fprintf (s, '%0.17f;' , dB(xi,1));     
    %end
    %fprintf(s,'\n');
    %BB = Bchoosen + dB;
    %fprintf(fileOutrageB, '%.17f;', BB);
    %fprintf(fileOutrageB,'\n');
    %fprintf(fileOutrageB,'\n');
%end

file1 = fopen('matrixForTime.csv', 'w');
fclose(file1);

file2 = fopen('freekoefForTime.csv', 'w');
fclose(file2);

file1 = fopen('matrixForTime.csv', 'a');

file2 = fopen('freekoefForTime.csv', 'a');

cond_val_time = 10;
fileX = fopen('rootsTime.csv', 'w');

fclose(fileX);

for n = 10:10:500
    X = randn(n, 1) * 10;

    fileX = fopen('rootsTime.csv', 'a');
    fprintf(fileX, '%.17f;', X);
    fprintf(fileX, '\n');
    fclose(fileX);
    D = diag(linspace(1, cond_val_time, n));
    [Q, R] = qr(rand(n)*20);
    A = Q*D*Q';
    AH = hess(A);
    cond(AH);    
    B = AH * X;
    fprintf(file2, '%.17f;', B);

    for j=1:n
        AR = AH(j,:);
        fprintf(file1, '%.17f;', AR);
        fprintf(file1, '\n');
    end
    fprintf(file1, '\n');
    fprintf(file2, '\n');
    fprintf(file2, '\n');
end

for n = 10:10:500
    X = randn(n, 1) * 10;
    D = diag(linspace(1, 10, n));
    [Q, R] = qr(rand(n)*20);
    A = Q*D*Q';
    A = hess(A);
    for j = 1:n
        for k = 1:n
            if j ~= k
                sum = sum + abs(A(j, k));
            end
        end
        for k = 1:n
            if j ~= k
                A(j, k) = A(j, k)/sum;
            end
        end
        sum = 0;
    end
    B = A * X;
    fprintf(fileBCompare, '%.17f;', B);
    for j=1:n
        AR = A(j,:);
        fprintf(fileCompare, '%.17f;', AR);
        fprintf(fileCompare, '\n');
    end
    fprintf(fileCompare, '\n');
    fprintf(fileBCompare, '\n');
    fprintf(fileBCompare, '\n');
end

fclose(file1);
fclose(file2);
fclose(fileCompare);
fclose(fileBCompare);

fclose(fileOutrageA);
fclose(fileOutrageB);