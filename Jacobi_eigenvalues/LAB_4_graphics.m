separability = importdata("separability.csv");
sep_value = importdata("sepValue.csv");

%ft = fittype("a*log(b*x)")
%f = fit(sep_value(:,1), separability(:,1), ft)
figure('name', 'Зависимость кол-ва итераций от числа отделимости');
semilogx(separability(1:12,1), separability(1:12,2));
hold on;
grid on;
%plot(f);
semilogx(separability(13:24,1), separability(13:24,2));
xlabel('Точность');
ylabel('Кол-во итераций');
%legend('измерения', 'аппроксимация');
title('Зависимость кол-ва итераций от точности');
legend('плохая отделимость (0.99)', 'хорошая отделимость (0.1)')

%исследование устойчивости=================================================

EigFromC = importdata("EigenValues.csv");
EigFromMatlab = importdata("EigFromMatlab.csv");
delta = [0.00001, 0.0001, 0.001, 0.01, 0.1, 1];
EigFromCSorted = zeros(10, 10);
%EigFromMatlabSorted = zeros(10, 10);
I1 = zeros(6, 10);
%I2 = zeros(6, 10);
[EigFromMatlabSorted(1,:), I2] = sort(EigFromMatlab(1,:));
for i=1:6
    [EigFromCSorted(i,:), I1(i,:)] = sort(EigFromC(i,:));
    AvgEig(i) = mean(abs((EigFromCSorted(i,:) - EigFromMatlabSorted(1,:))./EigFromMatlabSorted(1,:)));
    EigNorm(i) = norm(EigFromCSorted(i,:) - EigFromMatlabSorted(1,:))/norm(EigFromMatlabSorted(1,:));
    %EigNorm(i) = norm(sort(EigFromC(i,:)) - sort(EigFromMatlab(1,:)))/norm(sort(EigFromMatlab(1,:)));
end
% EigFromC
% EigFromMatlab
% EigNorm

figure('name', 'Устойчивость АПСЗ для собственных чисел')
loglog(delta, AvgEig);
hold on
grid on
xlabel('возмущение');
ylabel('отн. погрешность собственных чисел');
title('Устойчивость АПСЗ для собственных чисел');

eigenVectors = importdata("EigenVectors.csv");
eigenVectorsMatlab = importdata("EigenVectorsMatlab.csv");

vectors = zeros(10, 10);
I1;%=I1';
I2;%=I2';

for j=1:10
   vecMatlabForSort = eigenVectorsMatlab(j,:);
   eigenVectorsMatlab(j,:) = vecMatlabForSort(I2(1,:)); 
end

for i=1:6
    vectors = eigenVectors((i-1)*10+1:i*10,:);
    for j=1:10
        vecForSort = vectors(j,:);
        vectors(j,:) = vecForSort(I1(i,:));
        %vecMatlabForSort = eigenVectorsMatlab(j,:);
        %eigenVectorsMatlab(j,:) = vecMatlabForSort(I2(i,:));
        %eigenVectorsMatlab(:,j) = eigenVectorsMatlab(:,j)/norm(eigenVectorsMatlab(:,j));
    end
    for j=1:10
        if (vectors(1,j) * eigenVectorsMatlab(1,j) < 0)
            eigenVectorsMatlab(:,j) = -eigenVectorsMatlab(:,j);
        end
    end
   vectors;
   eigenVectorsMatlab;
   VectorsDiff = vectors - eigenVectorsMatlab;
   for j=1:10
       VectorsNorm(j) = norm(VectorsDiff(:,j))/norm(eigenVectorsMatlab(:,j));
   end
   AvgNorm(i) = mean(abs(VectorsNorm));
end

figure('name', 'Устойчивость АПСЗ для собственных векторов')
loglog(delta, AvgNorm);
hold on
grid on
xlabel('возмущение');
ylabel('средняя отн. погрешность нормы разности СВ');
title('Устойчивость АПСЗ для собственных векторов')

% for i=1:6
%    vectors
%    eigenVectorsMatlab
%    VectorsDiff = vectors - eigenVectorsMatlab
% end


%анализ времени работы=====================================================
% time = importdata("timeEigen.csv");
% 
% ft = fittype("alpha*x^3");
% f = fit(time(:,1), time(:,2), ft);
% 
% figure('name', 'Анализ времени работы')
% plot(time(:,1), time(:,2));
% hold on;
% grid on;
% plot(f);
% xlabel('Размерность');
% ylabel('Время');
% legend('Факическое измерение', 'Аппроксимированная прямая');
% title('Анализ времени работы');