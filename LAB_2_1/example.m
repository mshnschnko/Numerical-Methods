f = @(x) x.^2.*cos(2*x)+1;

figure
for n = 5:5:60
subplot(2,2,1)
a = -4;
b = -1;
fplot(f, [a,b]);
% n = 15;
x_i = linspace(a, b, n+1);
y_i = f(x_i);
hold on
grid on
plot(x_i, y_i, 'or');
coef = polyfit(x_i, y_i, n);
p = @(x) polyval(coef, x);
xx = linspace(a, b, 1000);
p_xx = p(xx);
hold on
plot(xx, p_xx, '--g');
legend('function', 'data', 'polynom');
title(['number of nodes = ', num2str(n+1)])
hold off

error = abs(p_xx - f(xx));
subplot(2,2,3)
% hold on
semilogy(xx, error);
grid on
max_err = max(error);
title(['error = ', num2str(max_err)])
% hold off
subplot(2,2,[2,4])
semilogy(n+1, max_err, '*r');
hold on
grid on
xlabel('number of nodes')
ylabel('max error')
pause(1);
end