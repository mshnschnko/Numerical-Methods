degree = importdata("degree.csv")
fileN = fopen('N.txt', 'r');
counts = fscanf(fileN, '%i %i');
fclose(fileN);
dimension = counts(1);
count = counts(2);
ft = fittype("alpha/x");
f = fit(degree(1:count,1), degree(1:count,2), ft);
figure('name', 'зависимость кол-ва итераций от степени диагонального преобладания')
plot(degree(2:count-1,1), degree(2:count-1,2))
hold on
grid on
plot(f);
%axis([0 60 0 30]);
title('зависимость кол-ва итераций от степени диагонального преобладания');
xlabel('степень диагонального преобладания');
ylabel('кол-во итераций');
legend('влияние степени ДП', 'аппроксимированная кривая')

time_measuring = importdata("time2.csv");
dimension = time_measuring(:,1);
time = time_measuring(:,2);
ft = fittype("alpha*x^3");
f = fit(dimension, time, ft);
figure('name', 'зависимость времени от размерности');
plot(f);
hold on
grid on
plot(dimension, time)
title('зависимость времени от размерности');
xlabel('размерность');
ylabel('время');
%figure('name', 'сравнение методов прогонки и Якоби')
%plot(degree(:,1), degree(:,2))
%hold on
%grid on
%title('сравнение методов прогонки и Якоби');
%xlabel('');
%ylabel('кол-во итераций');