%
% ESE 2014 : Some Lab_1 solutions
%
%
clear all;
close all;
clc;

%% problem 11:
%
% parameters
tmin=0;tmax=2*pi;ymin=-1.25;ymax=1.25;
Npts=2^10;
% variables
tr=linspace(0,2*pi,Npts); % create a time range (vector) of Npts points
omega_0=4;
y=sin(omega_0*tr);
% plot
figure;plot(tr,y,'.');title('sine wave for problem 11');grid;
xlabel('time [s]');ylabel('y');
axis([tmin tmax ymin ymax]);

%% problem 13:
%
% parameters
rng(59); % seed the random number generator for reproducible results
xmin=-100;xmax=+100;
ymin=-1.25;ymax=+1.25;
Npts=2^8;
% variables
xr=linspace(xmin,xmax,Npts);
ydata=2*(rand(1,Npts)-0.5*ones(1,Npts)); % transform data so it is from -1 to 1
ymean=mean(ydata)*ones(size(ydata));
%ydata=rand(1,Npts); % raw data from rand()

% plot
figure;plot(xr,ydata,'-',xr,ymean,'r--');
title('random data plot for problem 13');grid;
xlabel('independent variable');ylabel('data');
axis([xmin xmax ymin ymax]);
legend('data','mean');

%% problem 14
%
% parameters
rng(832); % seed the random number generator for reproducible results
xmin=-100;xmax=+100;
ymin=-1.25;ymax=+1.25;
Nss=5; % our sample size (number of points in "mini-mean" or sliding mean)
Np2=2^4; % our power of 2 (number of rows of Adata matrix)
Npts=Nss*Np2; % total number of points
% variables
xr=linspace(xmin,xmax,Npts); % random independent variable
ydata=2*(rand(1,Npts)-0.5*ones(1,Npts)); % transform data so it is from -1 to 1
Adata=reshape(ydata,[Nss,Np2])'; % data grouped in rows of five elements
MAdata=mean(Adata,2); % take mean value of each row, MAdata is of size Np2 x 1 
actual_mean=mean(ydata)*ones(size(MAdata)); % this is the mean value of the overall data set, in vector form
mean_diff=MAdata-actual_mean; % > 0 sample mean is greater than actual mean
greatert_string = 'greater than';
equal_string    = 'equal       ';
lesst_string    = 'less than   ';
for ii=1:Np2
    if(mean_diff(ii) > 0)
        diff_result(ii,:)=greatert_string;
    elseif (mean_diff(ii) < 0)
        diff_result(ii,:)=lesst_string;
    else
        diff_result(ii,:)=equal_string;
    end;
end;
Acomp = [num2str(mean_diff) diff_result];

%% problem 15
%
% parameters
tmin=0;tmax=2*pi;ymin=-2.5;ymax=2.5;
Npts=2^10;
% variables
tr=linspace(0,2*pi,Npts); % create a time range (vector) of Npts points
omega_0=4;
y1=sin(omega_0*tr);
y2=cos(2*omega_0*tr);
y3=sin(3*omega_0*tr);
y4=cos(4*omega_0*tr);
% call sumfuncs
Y = [ y1; y2; y3; y4];
ytotal=sumfuncs(Y);
% plot
figure;plot(tr,ytotal,'-');title('sum of sinusoids for problem 15');grid;
xlabel('time [s]');ylabel('ytotal');
axis([tmin tmax ymin ymax]);


