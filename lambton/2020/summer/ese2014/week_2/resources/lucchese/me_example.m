% Absorption measurement problem with sunlight for mechatronics students
% We want to measure signal absorbtion

% Signal
nv = 0:1000;
A = 10;
xv = A + randn(size(nv));
sv = 2000*sin(2*pi*(1:length(nv))/length(nv))./(1:length(nv))+10;

%% DC case
plot(nv,sv+xv,'b-',nv,A*ones(size(nv)),'k--',nv,sv,'r:');
xlabel('time (s)');
ylabel('Intensity');
axis([0 length(nv)-1 0 35]);
%title('Signal components at output');
legend('Measured signal','Transmission component','Sunlight component');

exportfig(gcf,'me_example1.eps','width',5,'height',2,'fontmode','fixed','Color','cmyk','fontsize',8);

%% AC case
fc = 0.025;
xvm = A/2*(sin(2*pi*fc*nv) + 1);
xvmn = xvm + randn(size(nv));
plot(nv,sv+xvmn,'b-',nv,xvm,'k--',nv,sv,'r:');
axis([0 length(nv)-1 0 35]);
%title('Signal components at output');
legend('Measured signal','Transmission component','Sunlight component');

exportfig(gcf,'me_example2.eps','width',5,'height',2,'fontmode','fixed','Color','cmyk','fontsize',8);
