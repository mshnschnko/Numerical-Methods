n = 10;
count = 100;
fileN = fopen("N.txt", "w");
fprintf(fileN, "%i %i", n, count);
fclose(fileN);
X = randn(n, 1) * 10;
cond_val = 10;
factor = linspace(1, 10, count);
fileX = fopen("roots.csv", "w");
fprintf(fileX, "%.17f;", X);
fclose(fileX);

fileA = fopen('matrixA.csv', 'w');
fclose(fileA);

fileB = fopen('matrixB.csv', 'w');
fclose(fileB);

fileA = fopen('matrixA.csv', 'a');

fileB = fopen('matrixB.csv', 'a');
sum = 0;
for i = 1:count
    D = diag(linspace(1, cond_val, n));
    [Q, R] = qr(rand(n)*20);
    A = Q*D*Q';
    for j = 1:n
        for k = 1:n
            if j ~= k
                sum = sum + abs(A(j, k));
            end
        end
        for k = 1:n
            if j ~= k
                A(j, k) = A(j, k)/(factor(i) * (sum));
            end
        end
        sum = 0;
    end
    B = A * X;
    fprintf(fileB, '%.17f;', B);
    for j=1:n
        AR = A(j,:);
        fprintf(fileA, '%.17f;', AR);
        fprintf(fileA, '\n');
    end
    fprintf(fileA, '\n');
    fprintf(fileB, '\n');
    fprintf(fileB, '\n');
end

fclose(fileA);
fclose(fileB);