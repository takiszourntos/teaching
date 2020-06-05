R = 1;  C = 1;
tau = R*C;
wb = 1/tau;
wv = 10.^(-1:0.001:2);
lwv = log10(wv);

% Magnitude response in db
Hm = 1./sqrt(1 + (wv/wb).^2);
Hmdb = 20*log10(Hm);

% Asymptotes
Hmdbs = zeros(size(wv));
Hmdbl = 20*log10(1./sqrt((wv/wb).^2));

ph1 = semilogx(wv,Hmdb,'r','LineWidth',2);  
xlabel('w');  ylabel('Gain GdB(w)');
hold on;
ph2 = semilogx(wv,Hmdbs,'b--','LineWidth',2);
ph3 = semilogx(wv,Hmdbl,'b--','LineWidth',2);
axis([min(wv) max(wv) -40 3]);
yt = -[0:10:40];  yta = sort([yt -10*log10(2)]);
set(gca,'YTick',yta);
ph4 = line([1 1],[-40 3]); set(ph4,'Color','k');
ph5 = line([1/10 1],[-3.1 -3.1]); set(ph5,'Color','k','LineStyle','--');
hold off;

exportfig(gcf,'rclpfbodemag.eps','width',4.5,'height',2.5,'fontmode','fixed', 'fontsize',8,'Color','cmyk');