leftdata = importdata("cmake-build-debug/LeftRectangle.csv");
rightdata = importdata("cmake-build-debug/RightRectangle.csv");
leftdataOpt = importdata("cmake-build-debug/LeftRectangleOpt.csv");
rightdataOpt = importdata("cmake-build-debug/RightRectangleOpt.csv");

leftaccuracy = 3 * leftdata(:,1);
leftcount = leftdata(:,2);
leftdots = leftdata(:,3);
leftvalue = leftdata(:,4);

rightaccuracy = 3 * rightdata(:,1);
rightcount = rightdata(:,2);
rightdots = rightdata(:,3);
rightvalue = rightdata(:,4);

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
loglog(leftaccuracy, abs(leftvalue - integral), 'LineWidth', 3);
hold on
grid on
%loglog(leftaccuracyOpt, abs(leftvalueOpt - integral), 'LineWidth', 2);
loglog(rightaccuracy, abs(rightvalue - integral), 'LineWidth', 2);
hold on
loglog(leftaccuracy,leftaccuracy);
legend('left rectangle', 'right rectangle');
title('dependence of error on accuracy');

%============== зависимость количества разбиений от точночти ==============
figure
loglog(leftaccuracy, leftcount, 'LineWidth', 3);
hold on
grid on
loglog(rightaccuracy, rightcount, 'LineWidth', 2);
legend('left rectangle', 'right rectangle');
title('dependence of count on accuracy');

%================ зависимость погрешности от точности ОПТ =================
figure
loglog(leftaccuracyOpt, abs(leftvalueOpt - integral), 'LineWidth', 3);
%loglog(rightaccuracy, abs(rightvalue - integral), 'LineWidth', 3);
hold on
grid on
loglog(rightaccuracyOpt, abs(rightvalueOpt - integral), 'LineWidth', 2);
hold on
loglog(leftaccuracyOpt,leftaccuracyOpt);
legend('left rectangle', 'right rectangle');
title('dependence of error on accuracy OPT');

%============ зависимость количества разбиений от точночти ОПТ ============
figure
loglog(leftaccuracyOpt, leftcountOpt, 'LineWidth', 3);
hold on
grid on
loglog(rightaccuracyOpt, rightcountOpt, 'LineWidth', 2);
legend('left rectangle', 'right rectangle');
title('dependence of count on accuracy OPT');

%=========== зависимость количества вызовов функций от точности ===========
figure
loglog(leftaccuracy, leftdots, leftaccuracyOpt, leftdotsOpt);
hold on
grid on
legend('w/a optimization', 'w/ optimization')
title ('left function calls count');

figure
loglog(rightaccuracy, rightdots, rightaccuracyOpt, rightdotsOpt);
hold on
grid on
legend('w/a optimization', 'w/ optimization')
title ('right function calls count');