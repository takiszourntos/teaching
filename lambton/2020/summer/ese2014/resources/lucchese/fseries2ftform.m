% Demonstration of Fourier transform from Fourier series, by increasing
% period
tmin = -10;  tmax = 10;
tv = tmin:0.001:tmax;
Tv = [2 4 8 16];

% Time domain
fh = figure;
for i=1:length(Tv);
  T = Tv(i);
  subplot(length(Tv),1,i);
  
  x1v = mod(tv,T);
  xv = zeros(size(tv));
  xv(x1v<1/2) = 1;
  xv(x1v>T-1/2) = 1;
  plot(tv,xv);
  axis([tmin tmax -0.25 1.25]);
  ylabel(sprintf('x%i(t)',T));
end
xlabel('t');  
exportfig(gcf,'fs2ft1.eps','width',6.8,'height',4,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
close(fh);

% Frequency domain
fh = figure;
wmin = -10;  wmax = 10;
for i=1:length(Tv);
  T = Tv(i);
  subplot(length(Tv),1,i);

  % Coefficients
  w0 = 2*pi/T;
  kmin = floor(wmin/w0);  kmax = ceil(wmax/w0);
  kv = kmin:kmax;
  wv = kv*w0;
  ckv = zeros(size(kv));
  for ki=1:length(kv)
    k = kv(ki);
    if k==0
      ckv(ki) = 1/T;
    else
      ckv(ki) = 1/(k*pi)*sin(k*pi/T);
    end
  end
  
  sh = stem(wv,T*abs(ckv),'filled');
  set(sh,'MarkerSize',3);
  ylabel(sprintf('%i|ck|',T));
  ax = axis;
  axis([wmin wmax ax(3) ax(4)]);
  set(gca,'XTick',[-3*pi -2*pi -pi 0 pi 2*pi 3*pi]);
  set(gca,'XTickLabel',{'-3pi','-2pi','-pi','0','pi','2pi','3pi'});
end
xlabel('w');  
exportfig(gcf,'fs2ft2.eps','width',6.8,'height',4,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
close(fh);

% Fourier transform
fh = figure;
wmin = -10;  wmax = 10;
wv = wmin:0.001:wmax;
Xw = sin(wv/2).*2./wv;

subplot(2,1,1);
plot(wv,abs(Xw));
ylabel('|X(w)|');
set(gca,'XTick',[-3*pi -2*pi -pi 0 pi 2*pi 3*pi]);
set(gca,'XTickLabel',{'-3pi','-2pi','-pi','0','pi','2pi','3pi'});

subplot(2,1,2);
plot(wv,angle(Xw));
ylabel('aX(w)');
xlabel('w');  
set(gca,'XTick',[-3*pi -2*pi -pi 0 pi 2*pi 3*pi]);
set(gca,'XTickLabel',{'-3pi','-2pi','-pi','0','pi','2pi','3pi'});
exportfig(gcf,'fs2ft3.eps','width',6.8,'height',2.3,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
close(fh);

