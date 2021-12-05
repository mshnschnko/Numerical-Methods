allMatrix = importdata("csvmatrix.csv");
filen = fopen('NNN.txt', 'r');
counts = fscanf(filen, '%i %i %i');
fclose(filen);
roots = importdata("roots.csv");
allRootsThomas = importdata("rootsThomas.csv");
allRootsThomasOutrage = importdata("rootsThomasOutrage.csv");
B = importdata("freekoef.csv");
OutrageB = importdata("OutrageB.csv");
Bchoosen = B(1,:);

dimensionOfMatrix = counts(1);
countOfMatrix = counts(2);
delta_len = counts(3);
row = 1;

condVal = [10, 10^2, 10^3, 10^4, 10^5, 10^6, 10^7, 10^8, 10^9, 10^(10)];
delta = [0.00001, 0.0001, 0.001, 0.01, 0.1, 1];

for i = 1:countOfMatrix
    matrix(1:dimensionOfMatrix,1:dimensionOfMatrix,i) = allMatrix(row:(row+dimensionOfMatrix-1), 1:dimensionOfMatrix, 1);
    row = row + dimensionOfMatrix;
end

for i = 1:countOfMatrix
    rootsThomas(i,:) = allRootsThomas(i,:);
end

for i = 1:delta_len
    rootsThomasOutrage(i,:) = allRootsThomasOutrage(i,:);
end

for i = 1:countOfMatrix
    err1(i) = norm(rootsThomas(i,:) - roots)/norm(roots);
end

for i = 1:delta_len
    err2(i) = norm(rootsThomasOutrage(i,:) - roots)/norm(roots);
end

for i = 1:delta_len
    errb(i) = norm(delta(i)*Bchoosen)/norm(Bchoosen);%norm(OutrageB(i,:) - Bchoosen)/norm(Bchoosen); %norm(delta(i)*Bchoosen)/norm(Bchoosen); %norm(OutrageB(i,:) - Bchoosen)/norm(Bchoosen);
end

figure('name', 'зависимость отн. погрешности от числа обусловленности');
loglog(condVal, err1, 'Color', 'red', 'LineWidth', 2);
hold on
grid on
title('зависимость отн. погрешности от числа обусловленности');
xlabel('число обусловленности');
ylabel('отн. погрешность норм');

figure('name', 'зависимость отн. погрешности от возмущения');
loglog(errb, err2, 'Color', 'green', 'LineWidth', 2);
hold on
grid on
title('зависимость отн. погрешности от возмущения');
xlabel('возмущение');
ylabel('отн. погрешность норм');

%figure;
%plot (x_B_SECOND,err_SECOND);
%hold on
%grid on
%title('relative error from cond ||dB||/||B||')
%xlabel ('||dB||/||B||')
%ylabel ('relative error || x - x* || / || x* ||')

for i=1:delta_len
    aa = norm(delta(i)*rootsThomas)/norm(roots);
    bb = cond(matrix(:,:,i))*norm(delta(i)*Bchoosen)/norm(Bchoosen);
    if aa <= bb
        display('TRUE')
    else
        display('FALSE')
    end
end
syms xxx;
y = xxx^3
time_measuring = importdata("time.csv");
dimension = time_measuring(:,1);
time = time_measuring(:,2);
ft = fittype("alpha*x");
f = fit(dimension, time, ft);
figure('name', 'зависимость времени от размерности');
plot(f);
hold on
grid on
plot(dimension, time)
title('зависимость времени от размерности');
xlabel('размерность');
ylabel('время');