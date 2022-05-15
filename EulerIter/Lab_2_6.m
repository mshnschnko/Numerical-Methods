once = importdata("EulerIterOnce.csv");
n1 = once(:, 1);
y_once = once(:, 2:end);

data = importdata("EulerIter.csv");
n = data(:,1);
y_1 = data(:,2);
y_n = data(:,3);
amount = data(:,4);

dataOP = importdata("EulerIterOutragePlus.csv");
nOP = dataOP(:,1);
yOP_1 = dataOP(:,2);
yOP_n = dataOP(:,3);
amountOP = dataOP(:,4);

dataOM = importdata("EulerIterOutrageMinus.csv");
nOM = dataOM(:,1);
yOM_1 = dataOM(:,2);
yOM_n = dataOM(:,3);
amountOM = dataOM(:,4);

Lab_5 = importdata("Y.csv");
n5 = Lab_5(:,1);
y1_5 = Lab_5(:,2);
yn_5 = Lab_5(:,3);

f = @(x) (2.*x+1)*log(2.*x+1)+1;
a = 0;
b = 4;

%=========================== графики функции ==============================
figure
fplot(f, [a,b], 'LineWidth', 3);
hold all
grid on
x1_1 = linspace(a, b, n1(1) + 1);
x1_2 = linspace(a, b, n1(2) + 1);
plot(x1_1, y_once(1,:), 'LineWidth', 2);
plot(x1_2, y_once(2,1:n1(2)+1), 'LineWidth', 2);
xlabel('x');
ylabel('y');
legend('exact solution', 'numerical solution n = 20', 'numerical solution n = 10');
title('func');

%=========================== графики ошибки ===============================
error1 = zeros(1, n1(1));
for i=1:n1(1)+1
    error1(i) = abs(f(x1_1(i)) - y_once(1,i));
end
figure
plot(x1_1, error1, 'LineWidth', 2);
hold on
grid on
xlabel('x');
ylabel('error');
title('error n = 20');

%=========================== графики ошибок ===============================
h = (b - a)./n;
error_local = zeros(1, 50);
error_global = zeros(1, 50);
for i=1:50
    error_local(i) = abs(f(a+h(i)) - y_1(i));
    error_global(i) = abs(f(b) - y_n(i));
end
figure
loglog(h, error_local, 'LineWidth', 2);
hold all
grid on
hhh = h.^3;
loglog(h, hhh, 'LineWidth', 2);
loglog(h, error_global, 'LineWidth', 2);
hh = h.^2;
loglog(h, hh, 'LineWidth', 2);
xlabel('h');
ylabel('error');
legend('local error', 'h^3', 'global error', 'h^2');
title('dependence of error on h');

%=============================== возмущение ===============================
delta = zeros(1, 14);
hO = (b-a)/nOP(1);
for i = 1:14
    delta(i) = 10^(-(15-i));
end
error_localOP = zeros(1, 14);
error_globalOP = zeros(1, 14);
error_localOM = zeros(1, 14);
error_globalOM = zeros(1, 14);
for i=1:14
    error_localOP(i) = abs(f(a+hO) - yOP_1(i));
    error_globalOP(i) = abs(f(b) - yOP_n(i));
    error_localOM(i) = abs(f(a+hO) - yOM_1(i));
    error_globalOM(i) = abs(f(b) - yOM_n(i));
end
figure
loglog(delta, error_localOP, 'LineWidth', 2);
hold all
grid on
loglog(delta, error_globalOP, 'LineWidth', 2);
loglog(delta, error_localOM, 'LineWidth', 2);
loglog(delta, error_globalOM, 'LineWidth', 2);
xlabel('delta');
ylabel('error');
% legend('local error PLUS', 'global error PLUS');
% legend('local error MINUS', 'global error MINUS');
legend('local error PLUS', 'global error PLUS', 'local error MINUS', 'global error MINUS');
title('dependence of error on outrage (n=25)');

%=============================== сравнение ================================
h = (b - a)./n;
error_local5 = zeros(1, 50);
error_global5 = zeros(1, 50);
for i=1:50
    error_local5(i) = abs(f(a+h(i)) - y1_5(1+(i-1)*10));
    error_global5(i) = abs(f(b) - yn_5(1+(i-1)*10));
end


figure
loglog(h, error_local, 'LineWidth', 2);
hold all
grid on
loglog(h, error_global, 'LineWidth', 2);
loglog(h, error_local5, 'LineWidth', 2);
loglog(h, error_global5, 'LineWidth', 2);
xlabel('h');
ylabel('error');
legend('local error w/ iter', 'global error w/ iter', 'local error w/a iter', 'global error w/a iter');
title('comparison 5 and 6 labs');