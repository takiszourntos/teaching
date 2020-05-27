
% Harmonic distortion caused by nonlinearity
% Input x(t) = cos(wt)

tv = 0:0.005:10;
w = 2*pi/2;
xv = cos(w*tv);
yv0 = 10*(xv + 5);
yv1 = (xv).^2;
yv2 = (xv + 1).^2;

% System y(t) = 10*(x(t) + 5)
% fh = figure;
% subplot(2,1,1);  
% plot(tv,xv);
% title('Input x(t)');
% subplot(2,1,2);
% plot(tv,yv0);
% title('Output y(t) = 10*\{x(t) + 5\}');

% % System y(t) = x(t)^2
% fh = figure;
% subplot(2,1,1);  
% plot(tv,xv);
% title('Input x(t)');
% subplot(2,1,2);
% plot(tv,yv1);
% title('Output y(t) = \{x(t)\}^2');

% System y(t) = (x(t) + 1)^2
fh = figure;
subplot(2,1,1);  
plot(tv,xv);
title('Input');
xlabel('t');  ylabel('x(t)');
subplot(2,1,2);
plot(tv,yv2);
title('Output');
xlabel('t');  ylabel('y(t)');

exportfig(gcf,'ee_example.eps','width',5,'height',3,'fontmode','fixed','Color','cmyk','fontsize',8);