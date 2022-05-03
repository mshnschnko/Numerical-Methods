data = importdata("Unew.csv");
n = data(:,1);
y = data(:,2:end);

outrage = importdata("outrage.csv");
no = outrage(1,1);
yo = outrage(:,2:end);

f = @(x) exp(-x.^2);

a = 0;
b = 1;
%30 = 21, 15 = 36
%=========================== графики функции ==============================
figure
fplot(f, [a,b], '--', 'LineWidth', 3);
hold all
grid on
x30 = linspace(a, b, n(21));
plot(x30, y(21,1:n(21)), 'LineWidth', 2);
x15 = linspace(a, b, n(36));
plot(x15, y(36,1:n(36)), 'LineWidth', 2);
xlabel('x');
ylabel('y');
legend('func', 'FDM n = 30', 'FDM n = 15');
title('solution graphic');

%=========================== графики ошибки ===============================
error20 = zeros(n(21),1);
error10 = zeros(n(36),1);
for i=1:n(21)
    error20(i) = abs(f(x30(i)) - y(21,i));
end
for i=1:n(36)
    error10(i) = abs(f(x15(i)) - y(36,i));
end
figure
plot(x30, error20, 'LineWidth', 3);
hold on
grid on
plot(x15, error10, 'LineWidth', 3);
xlabel('x');
ylabel('error');
legend('n = 30', 'n = 15');
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
loglog(h, h);
xlabel('h');
ylabel('error norm');
legend('error norm', 'diagonal');
title('Error norm');

%=============================== возмущение ===============================
delta = [0.0000001, 0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1];
xo = linspace(a, b, no);
normErrO = zeros(7, 1);
for i = 1:7
    normErrO(i) = norm(f(xo) - yo(i, :), inf);
end
figure
loglog(delta, normErrO, 'LineWidth', 3);
hold on
grid on
% loglog(h, h);
% xlabel('h');
ylabel('error norm');
% legend('error norm', 'diagonal');
title('Error norm with outrage');