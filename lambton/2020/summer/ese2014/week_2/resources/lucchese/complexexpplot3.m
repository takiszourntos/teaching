j = sqrt(-1);
t = 0:0.01:10+0.001;
omega = pi;
xv = exp(j*omega*t);

plot3(t,real(xv),imag(xv));
xlabel('t');  ylabel('real(e^{j (\pi) t})');  zlabel('imag(e^{j (\pi) t})');
% axis([min(t) max(t) -0.2 1.2]);
% subplot(2,1,2);  
% plot(t,angle(xv));
% xlabel('t');  ylabel('\angle (e^{j (2 \pi) t})');
[az,el] = view;  view(az+180,el);
grid on;

exportfig(gcf,'complexexpplot3.eps','width',4,'height',3,'fontmode','fixed','Color','cmyk','fontsize',8);