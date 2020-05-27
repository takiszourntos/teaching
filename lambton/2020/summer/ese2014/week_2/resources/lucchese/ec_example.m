% load sound sample
xv = wavread('16bit music.wav');
Fs = 10000;  % approximate sampling rate (where is this in the header?)

% Extract some samples and interpolate for display
ns = 30;
interpf = 20;
xvs = xv(1001:1000+ns);
xvsi = interp(xvs,interpf);
deltan = 1/Fs/interpf;
nvsi = deltan*((0:length(xvsi)-1)');

% Fiddle values for display
xvsi = xvsi - min(xvsi);

% Display first samples
subplot(3,1,1);
plot(nvsi,xvsi);
xlabel('time (s)');
ylabel('s(t)');
title('Samples of speech signal');
axis tight;

% Modulate samples
fc = 20000;
xvsim = xvsi.*cos(2*pi*fc*nvsi);
subplot(3,1,2);
plot(nvsi,xvsim,'b-',nvsi,xvsi,'k--',nvsi,-xvsi,'k--');
xlabel('time (s)');
ylabel('x(t)');
title('Samples modulated onto a carrier');
axis tight;

% Demodulate signals with envelope detector
lplen = 15;
xvsimd = xvsim.*cos(2*pi*fc*nvsi);
xvsimdlp = 2*convn(xvsimd,ones(lplen,1)/lplen,'same');
subplot(3,1,3);
plot(nvsi,xvsimd,'k-',nvsi,xvsimdlp,'b-');
xlabel('time (s)');
ylabel('y(t)');
title('Signal demodulated with envelope detector');
axis tight;

exportfig(gcf,'ec_example.eps','width',5,'height',5.5,'fontmode','fixed', 'fontsize',8);
%print(gcf,'-depsc2','demo_amplmod.eps');