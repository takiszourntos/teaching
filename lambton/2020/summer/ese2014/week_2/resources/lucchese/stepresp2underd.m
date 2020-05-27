tv = -2:0.01:10;
wn = 1;
zetav = [0.99 0.5 0.1];
gsc = cell(size(zetav));
for i=1:length(zetav)
  zeta = zetav(i);
  wd = wn*sqrt(1-zeta^2);
  gsc{i} = (1 - 1/sqrt(1-zeta^2)*exp(-zeta*wn*tv).*(sqrt(1-zeta^2)*cos(wd*tv)+zeta*sin(wd*tv))).*(tv>=0);
end

fh = figure;
ph = plot(tv, gsc{1}, 'r:', tv, gsc{2}, 'g-', tv, gsc{3}, 'b--', 'LineWidth', 2);
hold on;  plot(tv, tv>=0, 'k-');  hold off;
xlabel('t');  ylabel('Response');
legend('zeta=0.99','zeta=0.5','zeta=0.1');

exportfig(gcf,'stepresp2underd.eps','width',12,'height',6.0,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
close(fh);