tv = -1:0.001:2;
sv = sin(2*pi*tv);

subplot(3,1,1);
plot(tv,sv);
xlabel('t');  ylabel('x(t)');
subplot(3,1,2);
plot(tv,abs(sv));
xlabel('t');  ylabel('|x(t)|');
subplot(3,1,3);
asv = angle(sv);
plot(tv,asv);
%set(gca,'YLim', [-4 4]);
%set(gca,'YTick', [-pi 0 pi]);
%set(gca,'YTickLabel', {'-pi', '0', 'pi'});
set(gca,'YLim', [-1 4]);
set(gca,'YTick', [0 pi]);
set(gca,'YTickLabel', {'0', 'pi'});
xlabel('t');  ylabel('\angle x(t)');

exportfig(gcf,'sinmagphase.eps','width',5,'height',4,'fontmode','fixed','Color','cmyk','fontsize',8);