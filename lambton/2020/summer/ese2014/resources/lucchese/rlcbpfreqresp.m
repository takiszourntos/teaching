Rv = [0.2 2 10];  
R = 0.2;  C = 1;  L = 1;
wv = 10.^(-2:0.001:2);
lwv = log10(wv);

% Magnitude response in db
j = sqrt(-1);
Hc = cell(length(Rv),1);
for i=1:length(Rv)
  R = Rv(i);
  Hc{i} = (R + (j*wv)*L)./(1 + (j*wv)*R*C + (j*wv).^2*L*C);
end

fh = figure;
subplot(2,1,1);
ph1 = semilogx(wv, 20*log10(abs(Hc{1})), 'r:', wv, 20*log10(abs(Hc{2})), 'g-', wv, 20*log10(abs(Hc{3})), 'b--', 'LineWidth', 2);
legend('R=0.2','R=2','R=10');
ylabel('Gain GdB(w)');
subplot(2,1,2);
ph2 = semilogx(wv, angle(Hc{1}), 'r:', wv, angle(Hc{2}), 'g-', wv, angle(Hc{3}), 'b--', 'LineWidth', 2);
ylabel('aG(w)');
xlabel('w');

exportfig(gcf,'rlcbpfreqresp.eps','width',12,'height',7.5,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
close(fh);