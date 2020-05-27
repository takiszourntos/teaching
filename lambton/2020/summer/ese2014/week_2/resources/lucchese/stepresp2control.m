tv = -1:0.01:5;
sig7 = (1 - 7/6*exp(-tv) + 1/6*exp(-7*tv)).*(tv>=0);
sig16 = (1-(1+4*tv).*exp(-4*tv)).*(tv>=0);
sig80 = (1 - sqrt(5)/2*exp(-4*tv).*cos(8*tv+atan(-1/2))).*(tv>=0);

fh = figure;
ph = plot(tv, sig7, 'r:', tv, sig16, 'g-', tv, sig80, 'b--', 'LineWidth', 2);
hold on;  plot(tv, tv>=0, 'k-');  hold off;
xlabel('t');  ylabel('th(t)');
legend('K=7','K=16','K=80','Location','southeast');
axis([-1 5 -0.2 1.4]);

exportfig(gcf,'stepresp2control.eps','width',12,'height',6.0,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
%close(fh);