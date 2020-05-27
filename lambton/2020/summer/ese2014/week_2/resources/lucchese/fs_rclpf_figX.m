% The system I'm thinking about is a series combination of a resistor and a
% capacitor, with the input as voltage and the output the voltage across
% the resistor.  The differential equation is y(t) = RC d/dt x(t)

% Make the square wave
T = 2;
w0 = 2*pi/T;
R = 1;  C = 1;
ts = 0.001;  % small enough the we don't see artifacts
t = -2:ts:2;

% Original square wave
x0 = zeros(size(t));
x0(find(mod(t,2)<=0.5)) = 1;
x0(find(mod(t,2)>=1.5)) = 1;
x0 = x0 - 0.5;

% Signal FS coefficients
c0 = 0;
kv = 1:100;
ckv = 1./(kv*w0).*sin(kv*w0/2);
magckv = abs(ckv);  argckv = angle(ckv);
d0 = c0;
dkv = 1./(1+j*kv*w0*R*C).*ckv;
magdkv = abs(dkv);  argdkv = angle(dkv);

% Two term approximation to square wave from fourier series
c1 = 1/(1*w0)*sin(1*w0/2);  magc1 = abs(c1);  argc1 = angle(c1);
c3 = 1/(3*w0)*sin(3*w0/2);  magc3 = abs(c3);  argc3 = angle(c3);
xf0 = zeros(size(t)) + c0;
xf1 = 2*magc1*cos(1*w0*t + argc1);
xf3 = 2*magc3*cos(3*w0*t + argc3);

% Put each component through system
d0 = c0;
d1 = 1/(1+j*w0*R*C)*c1;  magd1 = abs(d1);  argd1 = angle(d1);
d3 = 1/(1+j*3*w0*R*C)*c3;  magd3 = abs(d3);  argd3 = angle(d3);
yf0 = zeros(size(t)) + d0;
yf1 = 2*magd1*cos(1*w0*t + argd1);
yf3 = 2*magd3*cos(3*w0*t + argd3);

% Display one component case
fh = figure;
vlim = [min(t) max(t) -1 1];  vlimr = [min(t) max(t) -0.3 0.3];
subplot(2,1,1);
plot(t,x0,'k-',t,xf0,'k-',t,xf1,'r--');  axis(vlim);
title('Input');
subplot(2,1,2);
plot(t,yf0,'k-',t,yf1,'r--');  axis(vlimr);
title('Output');
exportfig(gcf,'fs_rclpf_fig01.eps','width',10,'height',7.5,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
close(fh);

% Display two component case
fh = figure;
subplot(4,2,1);  
plot(t,xf0,'k-',t,xf1,'r--',t,xf3,'g--',t,xf0+xf1+xf3,'k-');  axis(vlim);
title('Input');
subplot(4,2,3);
plot(t,xf1,'r--');  axis(vlim);
title('Input component 1');
subplot(4,2,5);
plot(t,xf3,'g--');  axis(vlim);
title('Input component 2');
subplot(4,2,4);
plot(t,yf1,'r--');  axis(vlimr);
title('Output component 1');
subplot(4,2,6);
plot(t,yf3,'g--');  axis(vlimr);
title('Output component 2');
subplot(4,2,8);  
plot(t,yf0,'k-',t,yf1,'r--',t,yf3,'g--',t,yf0+yf1+yf3,'k-');  axis(vlimr);
title('Output');
exportfig(gcf,'fs_rclpf_fig02.eps','width',13,'height',8,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
close(fh);

% Input and output for increasing number of terms
Nv = [5 30];
for i=1:length(Nv)
  fh = figure;
  N = Nv(i);
  xf = zeros(size(t)) + c0;
  yf = zeros(size(t)) + d0;
  subplot(2,1,1);  plot(t,xf,'k-');
  subplot(2,1,2);  plot(t,yf,'k-');
  for k=1:N
    xfk = 2*magckv(k)*cos(k*w0*t + argckv(k));
    xf = xf + xfk;
    subplot(2,1,1);  hold on;  plot(t,xfk,'r--');  hold off;  axis(vlim);
    yfk = 2*magdkv(k)*cos(k*w0*t + argdkv(k));
    yf = yf + yfk;
    subplot(2,1,2);  hold on;  plot(t,yfk,'r--');  hold off;  axis(vlimr);
  end
  subplot(2,1,1);  hold on;  plot(t,xf,'k-');  hold off;
  title(sprintf('Input (N=%i)',N));
  subplot(2,1,2);  hold on;  plot(t,yf,'k-');  hold off;
  title('Output');
  outfile = sprintf('fs_rclpf_fig%02i.eps',i+2);
  exportfig(gcf,outfile,'width',10,'height',7.5,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
  %close(fh);
  pause;
end

% Bode plot for system
wv = -2*pi:0.001:2*pi;
Hv = 1./(1+j*wv*R*C);
subplot(2,1,1);
plot(wv,abs(Hv),'k-');
ax = axis;  ax(1) = -2*pi;  ax(2) = 2*pi;  axis(ax);
ylabel('|H(\omega)|');
set(gca,'XTick',[-2*pi -pi 0 pi 2*pi]);
set(gca,'XTickLabel',{'-2*pi','-pi','0','pi','2*pi'});
subplot(2,1,2);
plot(wv,zeros(size(wv)),'k-',wv,angle(Hv),'k-');
xlabel('\omega');  ylabel('\angle H(\omega)');
ax = axis;  ax(1) = -2*pi;  ax(2) = 2*pi;  axis(ax);
set(gca,'XTick',[-2*pi -pi 0 pi 2*pi]);
set(gca,'XTickLabel',{'-2*pi','-pi','0','pi','2*pi'});
exportfig(gcf,'fs_rclpf_fig05.eps','width',10,'height',7.5,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
close(fh);