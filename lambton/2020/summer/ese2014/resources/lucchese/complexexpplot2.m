j = sqrt(-1);
t = -2:0.01:10+0.001;
omega = pi;
xv = exp(j*omega*t);

subplot(2,1,1);  
plot(t,abs(xv));
xlabel('t');  ylabel('|e^{j (\pi) t}|');
axis([min(t) max(t) -0.2 1.2]);
subplot(2,1,2);  
plot(t,angle(xv));
xlabel('t');  ylabel('\angle (e^{j (\pi) t})');

exportfig(gcf,'complexexpplot2.eps','width',5,'height',3,'fontmode','fixed','Color','cmyk','fontsize',8);