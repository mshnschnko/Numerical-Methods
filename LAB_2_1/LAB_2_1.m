data = importdata("cmake-build-debug/TableValuesUniformGrid.csv");
x = data(:,1);
y = data(:,2);

data2 = importdata("cmake-build-debug/TableValuesChebGrid.csv");
x2 = data2(:,1);
y2 = data2(:,2);

%f = @(x) x.^2-sin(x)-0.25;
%f = @(x) x.^3 - exp(x) + 1;
f = @(x) x.^2.*cos(2*x) + 1;
a = -2.0;
b = 2.0;
i = 0;

% figure
% % for n = 3:2:7
%     fplot(f, [a, b], 'LineWidth', 3);
%     hold all
%     grid on
%     plot(x(i*100+1:(i+1)*100, :), y(i*100+1:(i+1)*100, :));
%     i = i + 1;
%     plot(x(i*100+1:(i+1)*100, :), y(i*100+1:(i+1)*100, :));
%     i = i + 1;
%     plot(x(i*100+1:(i+1)*100, :), y(i*100+1:(i+1)*100, :), 'g');
%     i = i + 1;
% % end
% legend('function', '4 nodes', '6 nodes', '8 nodes')
% title('Uniform grid')
% i = 0;
% figure
% % for n = 3:2:7
%     fplot(f, [a, b], 'LineWidth', 3);
%     hold all
%     grid on
%     plot(x2(i*100+1:(i+1)*100, :), y2(i*100+1:(i+1)*100, :));
%     i = i + 1;
%     plot(x2(i*100+1:(i+1)*100, :), y2(i*100+1:(i+1)*100, :));
%     i = i + 1;
%     plot(x2(i*100+1:(i+1)*100, :), y2(i*100+1:(i+1)*100, :), 'g');
%     i = i + 1;
% % end
% legend('function', '4 nodes', '6 nodes', '8 nodes')
% title('Chebyshev grid')
% 
% i = 0;
% 
% figure
% errorUni = abs(f(x(i*100+1:(i+1)*100, :)) - y(i*100+1:(i+1)*100, :));
% plot(x(i*100+1:(i+1)*100, :), errorUni)
% hold all
% grid on
% i = i + 1;
% errorUni = abs(f(x(i*100+1:(i+1)*100, :)) - y(i*100+1:(i+1)*100, :));
% plot(x(i*100+1:(i+1)*100, :), errorUni)
% i = i + 1;
% errorUni = abs(f(x(i*100+1:(i+1)*100, :)) - y(i*100+1:(i+1)*100, :));
% plot(x(i*100+1:(i+1)*100, :), errorUni)
% legend('4 nodes', '6 nodes', '8 nodes')
% title('Uniform error')
% 
% i = 0;
% 
% figure
% errorCheb = abs(f(x2(i*100+1:(i+1)*100, :)) - y2(i*100+1:(i+1)*100, :));
% plot(x2(i*100+1:(i+1)*100, :), errorCheb);
% hold all
% grid on
% i = i + 1;
% errorCheb = abs(f(x2(i*100+1:(i+1)*100, :)) - y2(i*100+1:(i+1)*100, :));
% plot(x2(i*100+1:(i+1)*100, :), errorCheb);
% i = i + 1;
% errorCheb = abs(f(x2(i*100+1:(i+1)*100, :)) - y2(i*100+1:(i+1)*100, :));
% plot(x2(i*100+1:(i+1)*100, :), errorCheb);
% legend('4 nodes', '6 nodes', '8 nodes')
% title('Chebyshev error')

% errorUni = zeros(1,12);
% errorCheb = zeros(1,12);
% for i=1:12
%     errorUni(i) = max(abs(f(x((i-1)*100+1:i*100, :)) - y((i-1)*100+1:i*100, :)));
%     errorCheb(i) = max(abs(f(x2((i-1)*100+1:i*100, :)) - y2((i-1)*100+1:i*100, :)));
% end
% n = linspace(5,60,12);
% figure
% semilogy(n+1, errorUni)
% hold on
% grid on
% semilogy(n+1, errorCheb)
% legend('Uniform', 'Chebyshev')
% title('Error dependence on the number of nodes')


% =========================== основная прога =============================
figure
for n = 5:5:60
subplot(2,2,1)
fplot(f, [a, b], 'LineWidth', 3);
grid on
hold all
plot(x(i*100'+1:(i+1)*100', :), y(i*100'+1:(i+1)*100', :), 'or');

plot(x2(i*100'+1:(i+1)*100', :), y2(i*100'+1:(i+1)*100', :), '*g');
hold off
legend('function', 'Uniform', 'Chebyshev');
title(['nodes count = ', num2str(n+1)]);

errorUni = abs(f(x(i*100'+1:(i+1)*100', :)) - y(i*100'+1:(i+1)*100', :));
errorCheb = abs(f(x2(i*100'+1:(i+1)*100', :)) - y2(i*100'+1:(i+1)*100', :));

subplot(2,2,3)
semilogy(x(i*100'+1:(i+1)*100', :), errorUni)
hold on
grid on
semilogy(x2(i*100'+1:(i+1)*100', :), errorCheb)
hold off
legend('Uniform', 'Chebyshev');
title('error')

subplot(2,2,[2,4])
semilogy(n+1, max(errorUni), '^r')
hold on
grid on
semilogy(n+1, max(errorCheb), 'ms')
legend('Uniform', 'Chebyshev');
%text(-1.1, 2.5, ['Uniform = ', num2str(max(errorUni))]);
title(['max error uniform = ', num2str(max(errorUni))], ['max error Cheb = ', num2str(max(errorCheb))])
i = i + 1;
pause(0.5);
end