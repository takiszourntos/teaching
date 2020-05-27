tv = -2:0.01:4;
yt = exp(-tv).*(tv>0);
plot(tv,yt);
xlabel('t');  ylabel('Output y(t)');
exportfig(gcf,'circuitrcparstepresp.eps','width',5,'height',1.5,'fontmode','fixed','Color','cmyk','fontsize',8);
