s = load('handel');

tv = (0:0.1:5)';
x = 5*s.y(1:length(tv));
y = double(tv>2);  y(tv>3.5) = -y(tv>3.5);

fh = figure;
plot(tv,x,'g--',tv,y,'r-.',tv,x.*y,'k-');
xlabel('t');  ylabel('Signal value');
axis([0 5 -1.1 1.1]);
legend('x(t)','y(t)','z(t) = x(t) y(t)','Location','NorthWest');
exportfig(gcf,'multsignalsex1.eps','width',5,'height',2,'fontmode','fixed','Color','cmyk','fontsize',8);

fh = figure;
plot(tv,x,'g--',tv,2*x,'k-');
xlabel('t');  ylabel('Signal value');
legend('x(t)','z(t) = 2 x(t)','Location','NorthWest');
exportfig(gcf,'multsignalsex2.eps','width',5,'height',2,'fontmode','fixed','Color','cmyk','fontsize',8);
