y1 = importdata("cmake-build-debug/Y_one.csv");
y = importdata("cmake-build-debug/Y.csv");
Runge = importdata("cmake-build-debug/Runge.csv");
n = y(:,1);

f = @(x) (2.*x+1)*log(2.*x+1)+1;
a = 0;
b = 4;

%=========================== графики функции ==============================
figure
plot(y1(:,1), y1(:,2), 'LineWidth', 2);
hold on
grid on
fplot(f, [a, b], 'LineWidth', 3);
xlabel('x')
ylabel('y')
legend('Euler', 'func')
title('solution graphic')

%=========================== графики ошибки ===============================
error = zeros(26,1);
for i=1:26
    error(i) = abs(f(y1(i,1)) - y1(i,2));
end
figure
plot(y1(:,1), error, 'LineWidth', 2);
hold on
grid on
% fplot(f, [a, b], 'LineWidth', 3);
xlabel('x')
ylabel('error')
% legend('Euler', 'func')
title('error graphic')

%=========================== графики ошибок ===============================
h = (b-a)./n;
localerror = zeros(491, 1);
globalerror = zeros(491, 1);
for i = 1:491
    localerror(i) = abs(f(a+h(i)) - y(i, 2));
    globalerror(i) = abs(f(b) - y(i, 3));
end

figure
loglog(h, localerror, 'LineWidth', 3)
hold all
grid on
loglog(h, globalerror, 'LineWidth', 3)
% loglog(h, h, 'LineWidth', 2)
xlabel('length')
ylabel('error')
legend('local error', 'global error')
title('error w/o Runge')


% err = zeros(491, 1);
% for i = 1:491
%     err(i) = abs(f(b) - y(i, 3));
% end
% 
% figure
% loglog(h, err, 'LineWidth', 3)
% hold on
% grid on
% loglog(h, h, 'LineWidth', 2)
% xlabel('length')
% ylabel('error')
% legend('error', 'diagonal')
% title('global error')

%================================= Объем ==================================
eps = Runge(:, 1);
n = Runge(:, 2);
k = Runge(:, 3);
yy = Runge(:, 4);
h = (b-a)./n;

figure
loglog(eps, k,  'LineWidth', 3);
hold on
grid on
xlabel('accuracy');
ylabel('amount');
title('dependence of amount on accuracy');

%================================= Рунге ==================================

figure
rungerror = zeros(length(yy), 1);
for i=1:length(yy)
    rungerror(i) = abs(f(b)-yy(i));
end
loglog(eps, rungerror, 'LineWidth', 3);
hold on
grid on
loglog(eps, eps, 'LineWidth', 2);
xlabel('accuracy')
ylabel('error')
title('Runge error')