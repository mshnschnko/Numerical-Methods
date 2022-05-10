data = importdata("Unew.csv");
n = data(:,1);
y = data(:,2:end);

outrage = importdata("outrage.csv");
no = outrage(1,1);
yo = outrage(:,2:end);

outrage2 = importdata("outrageMIN.csv");
no2 = outrage2(1,1);
yo2 = outrage2(:,2:end);

f = @(x) exp(-x.^2);

a = 0;
b = 1;
%30 = 21, 15 = 36
%=========================== графики функции ==============================
figure
fplot(f, [a,b], '--', 'LineWidth', 3);
hold all
grid on
x20 = linspace(a, b, n(48));
plot(x20, y(48,1:n(48)), 'LineWidth', 2);
x50 = linspace(a, b, n(46));
plot(x50, y(46,1:n(46)), 'LineWidth', 2);
xlabel('x');
ylabel('y');
legend('func', 'FDM n = 20', 'FDM n = 50');
title('solution graphic');

%=========================== графики ошибки ===============================
error20 = zeros(n(48),1);
error50 = zeros(n(46),1);
for i=1:n(48)
    error20(i) = abs(f(x20(i)) - y(48,i));
end
for i=1:n(46)
    error50(i) = abs(f(x50(i)) - y(46,i));
end
figure
plot(x20, error20, 'LineWidth', 3);
hold on
grid on
plot(x50, error50, 'LineWidth', 3);
xlabel('x');
ylabel('error');
legend('n = 20', 'n = 50');
title('error');

%=========================== норма погрешности ============================
h = (b-a)./(n-1);
normErr = zeros(length(n), 1);
for i = 1:length(n)
    x = linspace(a, b, n(i));
    normErr(i) = norm(f(x(1:n(i))) - y(i, 1:n(i)), inf);
end
figure
loglog(h, normErr, 'LineWidth', 3);
hold on
grid on
xlabel('h');
ylabel('error norm');
legend('error norm');
title('Error norm');

%=============================== возмущение ===============================
delta = [10^(-14), 10^(-13), 10^(-12), 10^(-11), 10^(-10), 10^(-9), 10^(-8), 10^(-7), 10^(-6), 10^(-5), 10^(-4), 10^(-3), 10^(-2), 10^(-1)];
xo = linspace(a, b, no);
normErrO = zeros(14, 1);
normErrO2 = zeros(14, 1);
for i = 1:14
    normErrO(i) = norm(f(xo) - yo(i, :), inf);
    normErrO2(i) = norm(f(xo) - yo2(i, :), inf);
end
figure
loglog(delta, normErrO, 'LineWidth', 3);
hold on
grid on
loglog(delta, normErrO2, 'LineWidth', 3);
% loglog(h, h);
% xlabel('h');
ylabel('error norm');
legend('error norm PLUS', 'error norm MINUS');
title('Error norm with outrage');

%========================== графики с возмущением =========================
figure
plot(xo, yo(14,:), 'LineWidth', 2);
hold all
grid on
plot(xo, yo2(14,:), 'LineWidth', 2);
plot(xo, y(1,:), 'LineWidth', 2);
fplot(f, [a,b], '--', 'LineWidth', 3);
xlabel('x');
ylabel('y');
legend('outrage plus', 'outrage minus', 'w/a outrage', 'func');
title('func with outrage = 1%, n = 500');
