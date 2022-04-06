data = importdata("cmake-build-debug/Gauss.csv");
leftdataOpt = importdata("cmake-build-debug/LeftRectangleOpt.csv");
rightdataOpt = importdata("cmake-build-debug/RightRectangleOpt.csv");

accuracy = data(:,1);
count = data(:,2);
value = data(:,3);

leftaccuracyOpt = 3 * leftdataOpt(:,1);
leftcountOpt = leftdataOpt(:,2);
leftdotsOpt = leftdataOpt(:,3);
leftvalueOpt = leftdataOpt(:,4);

rightaccuracyOpt = 3 * rightdataOpt(:,1);
rightcountOpt = rightdataOpt(:,2);
rightdotsOpt = rightdataOpt(:,3);
rightvalueOpt = rightdataOpt(:,4);

a = 0;
b = 3;

syms x;
f = x^2*cos(2*x)+1;
integral = double(int(f, a, b));

%================== зависимость погрешности от точности ===================
figure
loglog(accuracy, abs(value - integral), 'LineWidth', 3);
hold all
grid on
loglog(leftaccuracyOpt, abs(leftvalueOpt - integral), 'LineWidth', 3);
loglog(rightaccuracyOpt, abs(rightvalueOpt - integral), 'LineWidth', 2);
loglog(accuracy, accuracy);
xlabel('accuracy');
ylabel('error');
legend('Gauss', 'Left Rect', 'Right Rect');
title('dependence of error on accuracy');

%============== зависимость количества разбиений от точночти ==============
figure
semilogx(accuracy, count, 'LineWidth', 3);
grid on
xlabel('accuracy');
ylabel('devide count');
title('dependence of count on accuracy');

