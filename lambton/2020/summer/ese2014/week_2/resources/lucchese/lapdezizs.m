tv = 0:0.01:1.5;
yzsv = -1/8*sin(2*tv) - 1/16*exp(-2*tv) + 1/16*exp(2*tv);
yziv = exp(-2*tv);
yv = yzsv + yziv;

fh = figure;
ph = plot(tv, yzsv, 'r:', tv, yziv, 'g-', tv, yv, 'b--', 'LineWidth', 2);
xlabel('t');  ylabel('Response');
legend('yzs(t) ','yzi(t) ','y(t) ');

exportfig(gcf,'lapdezizs.eps','width',12,'height',4.5,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
%close(fh);