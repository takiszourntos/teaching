s = load('handel');

tv = 0:0.1:5;
x = s.y(1:length(tv));
y = double(tv>2)'/4;  y(tv>3.5) = -y(tv>3.5);

fh = figure;
plot(tv,x,'g--',tv,y,'r-.',tv,x+y,'k-');
xlabel('t');  ylabel('Signal value');
legend('x(t)','y(t)','z(t) = x(t) + y(t)','Location','NorthWest');
exportfig(gcf,'addsignalsex1.eps','width',5,'height',2,'fontmode','fixed','Color','cmyk','fontsize',8);

fh = figure;
plot(tv,x,'g--',tv,x+0.2,'k-');
xlabel('t');  ylabel('Signal value');
legend('x(t)','z(t) = x(t) + 0.2','Location','NorthWest');
exportfig(gcf,'addsignalsex2.eps','width',5,'height',2,'fontmode','fixed','Color','cmyk','fontsize',8);
