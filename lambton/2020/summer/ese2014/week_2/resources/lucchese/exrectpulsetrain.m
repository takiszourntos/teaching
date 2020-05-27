%% Calculate signal values and plot time domain representation
tv = -8:0.005:8;
xv = zeros(size(tv));
xv(mod(tv+2,8)<=4) = 1;
fh = figure;
ph = plot(tv,xv);
axis([-8 8 -0.2 1.2]);
xlabel('t (seconds)');  ylabel('x(t)');
exportfig(gcf,'exrectpulsetrain1.eps','width',5,'height',1.25,'fontmode','fixed','Color','cmyk','fontsize',8);
close(fh);

%% Calculate FS coefficients and plot freq domain representation
N = 20;
kvp = 1:N;  kvn = -fliplr(kvp);
kv = [kvn 0 kvp];
wv = kv*pi/4;
akv = sin(pi/2*kv)./(kv*pi);
akv(kv==0) = 1/2;

% Range to plot
Nd = 10;
ki = abs(kv)<=10;
kvd = kv(ki);
wvd = wv(ki);
akvd = akv(ki);

fh = figure;
subplot(2,1,1);
ph = stem(wvd,abs(akvd),'filled');
axis([min(wvd) max(wvd) 0 0.5]);
set(ph,'MarkerSize',3);
set(gca,'XTick',(-2:2)*pi);
set(gca,'XTickLabel',{'-2 pi','-pi','0','pi','2 pi'});
%set(gca,'YTick',[0 2.5 5]);
%set(gca,'YTickLabel',{'0','2.5','5'});
xlabel('w');  ylabel('|ak|');
subplot(2,1,2);
aakvd = angle(akvd);  aakvd = aakvd.*sign(kvd);
ph = stem(wvd,aakvd,'filled');
axis([min(wvd) max(wvd) -4 4]);
set(ph,'MarkerSize',3);
set(gca,'XTick',(-2:2)*pi);
set(gca,'XTickLabel',{'-2 pi','-pi','0','pi','2 pi'});
set(gca,'YTick',[-pi 0 pi]);
set(gca,'YTickLabel',{'-pi','0','pi'});
xlabel('w');  ylabel('ang ak');
exportfig(gcf,'exrectpulsetrain2.eps','width',5,'height',2.5,'fontmode','fixed','Color','cmyk','fontsize',8);
close(fh);

%% Reconstruction
Nv = [2 5 10 20];
fh = figure;
for i=1:length(Nv)
  rv = akv(kv==0)*ones(size(tv));
  for k=1:Nv(i)
    rv = rv + akv(kv==k)*exp(j*pi/4*k*tv);
    rv = rv + akv(kv==-k)*exp(-j*pi/4*k*tv);
  end
  subplot(length(Nv),1,i);
  plot(tv,rv);  xlabel('t');  ylabel(sprintf('xr%i(t)',Nv(i)));
  axis([-8 8 -0.5 1.5]);
end
exportfig(gcf,'exrectpulsetrain3.eps','width',5,'height',4.5,'fontmode','fixed','Color','cmyk','fontsize',8);
close(fh);

return;
