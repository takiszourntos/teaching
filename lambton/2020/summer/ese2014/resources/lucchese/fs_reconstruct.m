j = sqrt(-1);  % to be sure
tv = -6:0.001:14;  % time values (a row vector)
xv = zeros(size(tv));  % signal values initially zero
N = 10;  % highest term in synthesis equation
for k=-N:N
  % Current complex exponential values (a row vector)
  xcv = exp(j*k*pi/4*tv);
  
  % Coefficient for current complex exponential
  if k==0
    ck = 0;  % DC
  else
    ck = 4/((j*k*pi)^2)*(1 - exp(-j*k*pi));  % formula
    %ck = 1/(j*k*pi)*(1 - exp(-j*k*pi));  % y(t)
    %ck = 1/4*(1 - exp(-j*k*pi));  % z(t)
  end
  
  % Add scaled complex exponential to signal values
  xv = xv + ck*xcv;
end
plot(tv,real(xv));  % the values *should* be real
xlabel('t (seconds)');
ylabel('x_N(t)');
title(sprintf('Synthesised triangular waveform (N=%i)',N));
lh = line([0; 0], [ax(3); ax(4)]);  set(lh, 'color', 'k');
lh = line([ax(1); ax(2)], [0; 0]);  set(lh, 'color', 'k');
set(gca,'xtick',[-4 0 4 8 12]);
ax = [-6 14 -2.5 2.5];
axis(ax);
exportfig(gcf,'fs_additional_fig04.eps','width',10,'height',3,'fontmode','fixed', 'fontsize',8,'Color','cmyk');
