j = sqrt(-1);
t = -2:0.01:10;
omega = pi;
xv = exp(j*omega*t);

subplot(2,1,1);  
plot(t,real(xv));
xlabel('t');  ylabel('real(e^{j (\pi) t})');
subplot(2,1,2);  
plot(t,imag(xv));
xlabel('t');  ylabel('imag(e^{j (\pi) t})');

exportfig(gcf,'complexexpplot.eps','width',5,'height',3,'fontmode','fixed','Color','cmyk','fontsize',8);