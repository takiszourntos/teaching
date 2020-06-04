% Calculate signal values
tv = -6:0.01:14;
A = 2;
yv = zeros(size(tv));
yv(mod(tv,8)<=4) = 2;
yv = yv - 1;
xv = cumsum(yv);
xv = 2*xv/max(xv);

%% Plot triangular waveform
fh = figure;
plot(tv,xv);
xlabel('t (seconds)');
ylabel('x(t)');
ax = [-6 14 -2.5 2.5];
lh = line([0; 0], [ax(3); ax(4)]);  set(lh, 'color', 'k');
lh = line([ax(1); ax(2)], [0; 0]);  set(lh, 'color', 'k');
set(gca,'xtick',[-4 0 4 8 12]);
axis(ax);
exportfig(gcf,'fs_additional_fig01.eps','width',10,'height',3,'fontmode','fixed', 'fontsize',8,'Color','cmyk');

%% Plot derivative (rectangular) waveform
fh = figure;
plot(tv,yv);
xlabel('t (seconds)');
ylabel('y(t)');
ax = [-6 14 -1.25 1.25];
lh = line([0; 0], [ax(3); ax(4)]);  set(lh, 'color', 'k');
lh = line([ax(1); ax(2)], [0; 0]);  set(lh, 'color', 'k');
set(gca,'xtick',[-4 0 4 8 12]);
axis(ax);
exportfig(gcf,'fs_additional_fig02.eps','width',10,'height',3,'fontmode','fixed', 'fontsize',8,'Color','cmyk');

%% Plot second derivative (impulse train) waveform
% Using arrowh download
fh = figure;
ax = [-6 14 -3 3];
X1 = [-4 0 4 8 12; -4 0 4 8 12];
Y1 = [0 0 0 0 0; -2 2 -2 2 -2];
lh = line(X1,Y1);
set(lh,'Color','b');
ah = arrowh([-4,-4],[0,-2],'b');
ah = arrowh([0,0],[0,2],'b');
ah = arrowh([4,4],[0,-2],'b');
ah = arrowh([8,8],[0,2],'b');
ah = arrowh([12,12],[0,-2],'b');
xlabel('t (seconds)');
ylabel('z(t)');
lh = line([0; 0], [ax(3); ax(4)]);  set(lh, 'color', 'k');
lh = line([ax(1); ax(2)], [0; 0]);  set(lh, 'color', 'k');
set(gca,'xtick',[-4 0 4 8 12]);
axis(ax);  set(gca,'box','on')
exportfig(gcf,'fs_additional_fig03.eps','width',10,'height',3,'fontmode','fixed', 'fontsize',8,'Color','cmyk');

%% Plot exercise 3 waveform
ev3 = mod(tv,3)/3;
fh = figure;
plot(tv,ev3);
xlabel('t (seconds)');
ax = [-6 14 -0.25 1.25];
lh = line([0; 0], [ax(3); ax(4)]);  set(lh, 'color', 'k');
lh = line([ax(1); ax(2)], [0; 0]);  set(lh, 'color', 'k');
set(gca,'xtick',-6:3:14);
axis(ax);
exportfig(gcf,'fs_additional_fig07.eps','width',10,'height',3,'fontmode','fixed', 'fontsize',8,'Color','cmyk');

%% Plot exercise 4 waveform
yv4 = zeros(size(tv));
yv4(mod(tv-4,8)<=4) = 2;
yv4 = yv4 - 1;
ev4 = cumsum(yv4);
ev4 = 2*ev4/max(ev4);
fh = figure;
plot(tv,ev4);
xlabel('t (seconds)');
ylabel('x(t)');
ax = [-6 14 -2.5 2.5];
lh = line([0; 0], [ax(3); ax(4)]);  set(lh, 'color', 'k');
lh = line([ax(1); ax(2)], [0; 0]);  set(lh, 'color', 'k');
set(gca,'xtick',[-4 0 4 8 12]);
axis(ax);
exportfig(gcf,'fs_additional_fig08.eps','width',10,'height',3,'fontmode','fixed', 'fontsize',8,'Color','cmyk');

%% Check reconstruction with matlab
% Code moved to fs_reconstruct.m
eval('fs_reconstruct');

%% Frequency domain plots
N = 10;
kvp = 1:N;  kvn = -fliplr(kvp);
wv = [kvn 0 kvp]*pi/4;
dkv = [1./(j*kvn*pi).*(1 - exp(-j*kvn*pi)) 0 1./(j*kvp*pi).*(1 - exp(-j*kvp*pi))];
ckv = [4./((j*kvn*pi).^2).*(1 - exp(-j*kvn*pi)) 0 4./((j*kvp*pi).^2).*(1 - exp(-j*kvp*pi))];

%% Rectangular waveform
fh = figure;
subplot(2,1,1);  sh1 = stem(wv,abs(dkv),'filled');
set(gca,'XTick',(-2:2)*pi);
set(gca,'XTickLabel',{'-2 pi','-pi','0','pi','2 pi'});
ylabel('|d_k|');
title('Fourier series coefficients for rectangular wave');
adkv = angle(dkv);  adkv(abs(dkv)<eps) = 0;
subplot(2,1,2);  sh2 = stem(wv,adkv,'filled');
set(gca,'XTick',(-2:2)*pi);
set(gca,'XTickLabel',{'-2 pi','-pi','0','pi','2 pi'});
ylabel('\angle d_k');  xlabel('\omega');
set([sh1; sh2],'MarkerSize',2);
exportfig(gcf,'fs_additional_fig05.eps','width',10,'height',6.5,'fontmode','fixed', 'fontsize',8,'Color','cmyk');

%% Triangular waveform
fh = figure;
subplot(2,1,1);  sh1 = stem(wv,abs(ckv),'filled');
set(gca,'XTick',(-2:2)*pi);
set(gca,'XTickLabel',{'-2 pi','-pi','0','pi','2 pi'});
ylabel('|c_k|');
title('Fourier series coefficients for triangular wave');
ackv = angle(ckv);  ackv(abs(ckv)<eps) = 0;
subplot(2,1,2);  sh2 = stem(wv,ackv,'filled');
set(gca,'XTick',(-2:2)*pi);
set(gca,'XTickLabel',{'-2 pi','-pi','0','pi','2 pi'});
ylabel('\angle c_k');  xlabel('\omega');
set([sh1; sh2],'MarkerSize',2);
exportfig(gcf,'fs_additional_fig06.eps','width',10,'height',6.5,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
