tv = -5:0.01:5;
sig1 = 0.1;  w1 = 10;  a1 = 1;  ph1 = 0.2;
xvf1 = a1*cos(w1*tv+ph1);
xvl1 = a1*exp(sig1*tv).*cos(w1*tv+ph1);
sig2 = 0.1;  w2 = 3;  a2 = 1.7;  ph2 = 0.4;
xvf2 = a2*cos(w2*tv+ph2);
xvl2 = a2*exp(sig1*tv).*cos(w2*tv+ph2);

fh = figure;
subplot(2,1,1);
plot(tv,xvf1,'g-',tv,xvf2,'r-','LineWidth',2);  axis([-5 5 -2 2]);
xlabel('t');  ylabel('Fourier basis');
subplot(2,1,2);
plot(tv,xvl1,'g-',tv,xvl2,'r-','LineWidth',2);  axis([-5 5 -3 3]);
xlabel('t');  ylabel('Laplace basis');
exportfig(gcf,'laplacerecbasis.eps','width',12,'height',7.5,'fontmode','fixed','Color','cmyk','fontsize',8);

