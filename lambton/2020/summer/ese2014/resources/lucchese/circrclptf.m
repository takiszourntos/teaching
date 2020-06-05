R = 1;  C = 1;

% Bode plot for system
fh = figure;
wv = -6:0.001:6;
Hv = 1./(1+j*wv*R*C);
subplot(2,1,1);
plot(wv,abs(Hv),'r-','LineWidth',2);
ax = axis;  ax(1) = min(wv);  ax(2) = max(wv);  axis(ax);
ylabel('|H(w)|');
%set(gca,'XTick',[-2*pi -pi 0 pi 2*pi]);
%set(gca,'XTickLabel',{'-2*pi','-pi','0','pi','2*pi'});
subplot(2,1,2);
ph1 = plot(wv,zeros(size(wv)),'k-');  hold on;
ph2 = plot(wv,angle(Hv),'r-','LineWidth',2);
xlabel('\omega');  ylabel('aH(w)');
%ax = axis;  ax(1) = -2*pi;  ax(2) = 2*pi;  axis(ax);
%set(gca,'XTick',[-2*pi -pi 0 pi 2*pi]);
%set(gca,'XTickLabel',{'-2*pi','-pi','0','pi','2*pi'});
exportfig(gcf,'circrclptf.eps','width',5,'height',3,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
%close(fh);