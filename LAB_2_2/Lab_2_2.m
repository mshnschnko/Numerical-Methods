data = importdata("cmake-build-debug/QuadSpline.csv");
x = data(:,1);
y = data(:,2);
% data = importdata("cmake-build-debug/TableValuesUniformGrid.csv");
data = importdata("cmake-build-debug/TableValuesUniformGrid11.csv");
x1 = data(:,1);
y1 = data(:,2);

f = @(x) x.^2.*cos(2*x) + 1;
a = -2.0;
b = 2.0;
i = 0;
% pause(5);
%============================ графики функций =============================

% figure
% fplot(f, [a, b], 'LineWidth', 3);
% hold all
% grid on
% plot(x(i*200+1:(i+1)*200, :), y(i*200+1:(i+1)*200, :));
% i = i + 1;
% plot(x(i*200+1:(i+1)*200, :), y(i*200+1:(i+1)*200, :));
% i = i + 1;
% plot(x(i*200+1:(i+1)*200, :), y(i*200+1:(i+1)*200, :), 'g');
% i = i + 1;
% legend('function', '4 nodes', '6 nodes', '8 nodes')
% title('Uniform grid')
% axis([-2.5 2.5 -3 3])
% i = 0;

%============================ графики ошибок ==============================

% figure
% error = abs(f(x(i*100+1:(i+1)*100, :)) - y(i*100+1:(i+1)*100, :));
% plot(x(i*100+1:(i+1)*100, :), error)
% hold all
% grid on
% i = i + 1;
% error = abs(f(x(i*100+1:(i+1)*100, :)) - y(i*100+1:(i+1)*100, :));
% plot(x(i*100+1:(i+1)*100, :), error)
% i = i + 1;
% error = abs(f(x(i*100+1:(i+1)*100, :)) - y(i*100+1:(i+1)*100, :));
% plot(x(i*100+1:(i+1)*100, :), error)
% legend('4 nodes', '6 nodes', '8 nodes')
% title('Spline error')
% i = 0;
% 
% figure
% error = abs(f(x1(i*100+1:(i+1)*100, :)) - y1(i*100+1:(i+1)*100, :));
% plot(x1(i*100+1:(i+1)*100, :), error)
% hold all
% grid on
% i = i + 1;
% error = abs(f(x1(i*100+1:(i+1)*100, :)) - y1(i*100+1:(i+1)*100, :));
% plot(x1(i*100+1:(i+1)*100, :), error)
% i = i + 1;
% error = abs(f(x1(i*100+1:(i+1)*100, :)) - y1(i*100+1:(i+1)*100, :));
% plot(x1(i*100+1:(i+1)*100, :), error)
% legend('4 ndes', '6 nodes', '8 nodes')
% title('Lagrange error')
% i = 0;

%======================= полный график ошибок =============================

% errorSpline = zeros(1,36);
% errorLagrange = zeros(1,36);
% 
% for i=1:36
%     errorSpline(i) = max(abs(f(x((i-1)*200+1:i*200, :)) - y((i-1)*200+1:i*200, :)));
%     errorLagrange(i) = max(abs(f(x1((i-1)*100+2:i*100-1, :)) - y1((i-1)*100+2:i*100-1, :)));
% end
% n = linspace(5,180,36);
% figure
% h = (b-a)./n;
% semilogy(h, errorLagrange, 'LineWidth', 2)
% %semilogy(n+1, errorSpline, 'LineWidth', 3)
% hold on
% grid on
% semilogy(h, errorSpline, 'LineWidth', 3)
% % for i=1:36
%     %errorSpline(i) = max(abs(f(x((i-1)*200+1:i*200, :)) - y((i-1)*200+1:i*200, :)));
%     %errorLagrange(i) = max(abs(f(x1((i-1)*100+2:i*100-1, :)) - y1((i-1)*100+2:i*100-1, :)));
% % end
% % n = linspace(5,180,36);
% % h = (b-a)./n;
% % loglog(h, errorSpline, 'LineWidth', 3)
% %semilogy(n+1, errorLagrange, 'LineWidth', 2)
% legend('Lagrange', 'Spline')
% title('Error dependence on the number of nodes')

% =========================== основная прога =============================
% i = 0;
% figure
% for n = 5:5:180
% nodes = linspace(a, b, n);
% subplot(2,2,1)
% fplot(f, [a, b], 'LineWidth', 3);
% grid on
% hold all
% plot(x(i*200'+1:(i+1)*200', :), y(i*200'+1:(i+1)*200', :));
% plot(x1(i*100'+1:(i+1)*100', :), y1(i*100'+1:(i+1)*100', :));
% plot(nodes, f(nodes), 'og');
% hold off
% legend('function', 'Spline', 'Lagrange');
% title(['nodes count = ', num2str(n+1)]);
% 
% errorSpline = abs(f(x(i*200'+1:(i+1)*200', :)) - y(i*200'+1:(i+1)*200', :));
% errorLagrange = abs(f(x1(i*100'+1:(i+1)*100', :)) - y1(i*100'+1:(i+1)*100', :));
% h = (b-a)/n;
% 
% subplot(2,2,3)
% semilogy(x(i*200'+1:(i+1)*200', :), errorSpline)
% hold on
% grid on
% semilogy(x1(i*100'+1:(i+1)*100', :), errorLagrange)
% hold off
% legend('Spline', 'Lagrange');
% title('error')
% 
% subplot(2,2,[2,4])
% loglog(h, max(errorSpline), '^r')
% hold on
% grid on
% loglog(h, max(errorLagrange), 'ms')
% legend('Spline', 'Lagrange');
% %text(-1.1, 2.5, ['Uniform = ', num2str(max(errorSpline))]);
% title(['max error spline = ', num2str(max(errorSpline))], ['max error lagrange = ', num2str(max(errorLagrange))])
% i = i + 1;
% pause(0.5);
% end

% =============================== 10 баллов ===============================
data = importdata("cmake-build-debug/PerturbatedSpline.csv");
xp = data(:,1);
yp = data(:,2);
delta = [10^(-7), 10^(-6), 10^(-5), 10^(-4), 10^(-3), 10^(-2), 10^(-1), 1, 10, 100, 1000];
cnt = length(delta);
errorP = zeros(1,cnt);
figure
for i = 1:1:cnt
    subplot(2,1,1)
    fplot(f, [a, b], 'LineWidth', 3);
    hold on
    grid on
    plot(xp((i-1)*200+1:i*200, :), yp((i-1)*200+1:i*200, :), 'LineWidth', 2);
    hold off
    legend('function', 'perurbated')
    title('dependence on perturbation', ['delta = ', num2str(100 * delta(i)), '%'])
    subplot(2,1,2)
    
    errorP(i) = max(abs(f(xp((i-1)*200+1:i*200, :)) - yp((i-1)*200+1:i*200, :)));
    loglog(delta(i), errorP(i), '*r');
    hold on
    grid on
    title('Error')
    pause(1);
end




% g1 = @(x) 6.72594.*x.^2+23.4639.*x+18.4095;
% g2 = @(x) -7.31877.*x.^2-10.2434.*x-1.81488;
% g3 = @(x) 5.48546.*x.^2-0.000002.*x+0.2338;
% g4 = @(x) -7.31877.*x.^2+10.2434.*x-1.81488;
% g5 = @(x) 6.72594.*x.^2-23.4639.*x+18.4095;
% x1 = linspace(-2, -1.2, 50);
% x2 = linspace(-1.2, -0.4, 50);
% x3 = linspace(-0.4, 0.4, 50);
% x4 = linspace(0.4, 1.2, 50);
% x5 = linspace(1.2, 2, 50);
% figure
% fplot(f, [a,b], 'LineWidth', 3)
% hold all
% grid on
% % fplot(g1, [-2, -1.2], 'r')
% % fplot(g2, [-1.2, -0.4], 'g')
% % fplot(g3, [-0.4, 0.4], 'b')
% % fplot(g4, [0.4, 1.2], 'magenta')
% % fplot(g5, [1.2, 2], 'c')
% plot(x1, g1(x1), 'r')
% plot(x2, g2(x2), 'g')
% plot(x3, g3(x3), 'b')
% plot(x4, g4(x4), 'magenta')
% plot(x5, g5(x5), 'c')
% legend('function', 'g_1', 'g_2', 'g_3', 'g_4', 'g_5')
% title('test example')