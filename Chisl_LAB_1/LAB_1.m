x = [-2:0.01:32];
f = @(x) 2.*x.^5 + 3.*x.^4 - 4.*x.^3 - 12.*x.^2 + 10;
df = @(x) 10.*x.^4 + 12.*x.^3 - 12.*x.^2 - 24.*x;
g = @(x) sin(x) - 5.^x + 3;
dg = @(x) cos(x) - log(5)*5.^x;

x1 = [-2:0.1:5];
kasAlg1 = @(x) f((1.3 + 3)/2) + df((1.3 + 3)/2).*(x-(1.3 + 3)/2);
kasAlg2 = @(x) f((1.3306172417945143 + 2.0478166653095631)/2) + df((1.3306172417945143 + 2.0478166653095631)/2).*(x-(1.3306172417945143 + 2.0478166653095631)/2);
kasAlg3 = @(x) f((1.4311887664342158 + 1.5988735751654100)/2) + df((1.4311887664342158 + 1.5988735751654100)/2).*(x-(1.4311887664342158 + 1.5988735751654100)/2);
kasAlg4 = @(x) f((1.5035181637950406 + 1.5052010170120060)/2) + df((1.5035181637950406 + 1.5052010170120060)/2).*(x-(1.5035181637950406 + 1.5052010170120060)/2);
kasAlg5 = @(x) f((1.5043907991988430 + 1.5043907992170509)/2) + df((1.5043907991988430 + 1.5043907992170509)/2).*(x-(1.5043907991988430 + 1.5043907992170509)/2);

kasTrans1 = @(x) g((0.8 + 2)/2) + dg((0.8 + 2)/2).*(x-(0.8 + 2)/2);
kasTrans2 = @(x) g((0.81175556377672686 + 1.08673155920815100)/2) + dg((0.81175556377672686 + 1.08673155920815100)/2).*(x-(0.81175556377672686 + 1.08673155920815100)/2);
kasTrans3 = @(x) g((0.81780288475485774 + 0.82086995450442923)/2) + dg((0.81780288475485774 + 0.82086995450442923)/2).*(x-(0.81780288475485774 + 0.82086995450442923)/2);
kasTrans4 = @(x) g((0.81788010722595184 + 0.81788010730192906)/2) + dg((0.81788010722595184 + 0.81788010730192906)/2).*(x-(0.81788010722595184 + 0.81788010730192906)/2);

syms xx;
y=xx;

rf = fzero(f, [1.5, 1.6]); %точный корень алгебраической
rg = fzero(g, [0.7, 0.9]); %точный корень трансцендентной

BisAlgOnes = importdata("BisAlgOnes.csv");
IterBisAlgOnes = BisAlgOnes(:,1)';
AbsErrBisAlgOnes = abs(BisAlgOnes(:,2)'-rf);

BisTransOnes = importdata("BisTransOnes.csv");
IterBisTransOnes = BisTransOnes(:,1)';
AbsErrBisTransOnes = abs(BisTransOnes(:,2)'-rg);

ComboAlgOnes = importdata("ComboAlgOnes.csv");
IterComboAlgOnes = ComboAlgOnes(:,1)';
AbsErrComboAlgOnes = abs(ComboAlgOnes(:,2)'-rf);

ComboTransOnes = importdata("ComboTransOnes.csv");
IterComboTransOnes = ComboTransOnes(:,1)';
AbsErrComboTransOnes = abs(ComboTransOnes(:,2)'-rg);

figure('name', 'графики функций');
plot(x, f(x));
hold all
grid on
plot(x, g(x), 'LineWidth', 3);
line([1.3, 3], [f(1.3), f(3)], 'Color', 'magenta');
line([1.3099330694717686, 2.4517819707683763], [f(1.3099330694717686), f(2.4517819707683763)], 'Color', 'magenta');
line([1.3306172417945143, 2.0478166653095631], [f(1.3306172417945143), f(2.0478166653095631)], 'Color', 'magenta');
line([1.3701496779774778, 1.7685600186925623], [f(1.3701496779774778), f(1.7685600186925623)], 'Color', 'magenta');
line([1.4311887664342158, 1.5988735751654100], [f(1.4311887664342158), f(1.5988735751654100)], 'Color', 'magenta');
line([1.4864641415270146, 1.5222010228736806], [f(1.4864641415270146), f(1.5222010228736806)], 'Color', 'magenta');
line([1.5035181637950406, 1.5052010170120060], [f(1.5035181637950406), f(1.5052010170120060)], 'Color', 'magenta');
line([1.5043888658810258, 1.5043925882863483], [f(1.5043888658810258), f(1.5043925882863483)], 'Color', 'magenta');
line([1.5043907991988430, 1.5043907992170509], [f(1.5043907991988430), f(1.5043907992170509)], 'Color', 'magenta');
plot(x1, kasAlg1(x1), 'Color', 'black');
plot(x1, kasAlg2(x1), 'Color', 'black');
plot(x1, kasAlg3(x1), 'Color', 'black');
plot(x1, kasAlg4(x1), 'Color', 'black');
plot(x1, kasAlg5(x1), 'Color', 'black');

line([0.8, 2], [g(0.8), g(2)], 'Color', 'green');
line([0.80529401803910050, 1.48119026199459110], [g(0.80529401803910050), g(1.48119026199459110)], 'Color', 'green');
line([0.81175556377672686, 1.08673155920815100], [g(0.81175556377672686), g(1.08673155920815100)], 'Color', 'green');
line([0.81645120428045004, 0.87461884013418578], [g(0.81645120428045004), g(0.87461884013418578)], 'Color', 'green');
line([0.81780288475485774, 0.82086995450442923], [g(0.81780288475485774), g(0.82086995450442923)], 'Color', 'green');
line([0.81787988200889061, 0.81788881494729604],[g(0.81787988200889061), g(0.81788881494729604)], 'Color', 'green');
line([0.81788010722595184, 0.81788010730192906], [g(0.81788010722595184), g(0.81788010730192906)], 'Color', 'green');
plot(x1, kasTrans1(x1), 'Color', 'cyan');
plot(x1, kasTrans2(x1), 'Color', 'cyan');
plot(x1, kasTrans3(x1), 'Color', 'cyan');
plot(x1, kasTrans4(x1), 'Color', 'cyan');

title('графики функций');
axis([-2, 2, -15, 15]);
xlabel('x');
ylabel('y');
legend('Алгебраическая', 'Трансцендентная');

figure('name', 'Сходимость');
semilogy(IterBisAlgOnes, AbsErrBisAlgOnes, IterBisTransOnes, AbsErrBisTransOnes, IterComboAlgOnes, AbsErrComboAlgOnes, IterComboTransOnes, AbsErrComboTransOnes);
hold on
grid on
title('Сходимость (e = 10^{-7})');
xlabel('номер итерации');
ylabel('абсолютная погрешность');
legend('МПД алгебра', 'МПД транс', 'Комбо алгебра', 'Комбо транс');

BisAlg = importdata("BisAlg.csv");
IterCountBisAlg = BisAlg(:,1)';
AbsErrBisAlg = abs(BisAlg(:,2)'-rf);
ErrBisAlg = BisAlg(:,3)';

BisTrans = importdata("BisTrans.csv");
IterCountBisTrans = BisTrans(:,1)';
AbsErrBisTrans = abs(BisTrans(:,2)'-rg);
ErrBisTrans = BisTrans(:,3)';

ComboAlg = importdata("ComboAlg.csv");
IterCountComboAlg = ComboAlg(:,1)';
AbsErrComboAlg = abs(ComboAlg(:,2)'-rf);
ErrComboAlg = ComboAlg(:,3)';

ComboTrans = importdata("ComboTrans.csv");
IterCountComboTrans = ComboTrans(:,1)';
AbsErrComboTrans = abs(ComboTrans(:,2)'-rg);
ErrComboTrans = ComboTrans(:,3)';

figure('name', 'Объём вычислений');
semilogx(ErrBisAlg, IterCountBisAlg, ErrBisTrans, IterCountBisTrans, ErrComboAlg, IterCountComboAlg, ErrComboTrans, IterCountComboTrans);
hold on
grid on
title('Объём вычислений');
xlabel('точность');
ylabel('количество итераций');
legend('МПД алгебра', 'МПД транс', 'Комбо алгебра', 'Комбо транс');

figure('name', 'Достижение точности');
loglog(ErrBisAlg, AbsErrBisAlg, ErrBisTrans, AbsErrBisTrans, ErrComboAlg, AbsErrComboAlg, ErrComboTrans, AbsErrComboTrans);
hold on
fplot(y);
grid on
title('Достижение точности');
xlabel('точность');
ylabel('абсолютная погрешность');
legend('МПД алгебра', 'МПД транс', 'Комбо алгебра', 'Комбо транс');

Udal = importdata("Udal.csv");
Dist = Udal(:,1)';
DistAlg=Dist+3-rf;
DistTrans=Dist+2-rg;
IterCountBisAlgUdal = Udal(:,2)';
IterCountBisTransUdal = Udal(:,3)';
IterCountComboAlgUdal = Udal(:,4)';
IterCountComboTransUdal = Udal(:,5)';

figure('name', 'Влияние х(0)');
plot(DistAlg, IterCountBisAlgUdal, 'LineWidth', 5, 'Color', 'green');
hold all
plot(DistTrans, IterCountBisTransUdal, 'LineWidth', 2, 'Color', 'red');
plot(DistAlg, IterCountComboAlgUdal, DistTrans, IterCountComboTransUdal);
grid on
title('Влияние х(0) (e = 10^{-7})');
xlabel('Удаленность от корня');
ylabel('Количество итераций');
legend('МПД алгебра', 'МПД транс', 'Комбо алгебра', 'Комбо транс');