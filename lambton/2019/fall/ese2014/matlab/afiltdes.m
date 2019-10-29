%% analog filter designer
% 
% starter code by Takis Zourntos (C) 2019
%   please modify to use with other filter families
%
clear all;
close all;
pack;

% Butterworth
N=3; % order 
Fc = 15000; % butterworth "3-dB" frequency
[num, den] = butter(N,2*pi*Fc,'s'); % design continuous-time Butterworth filter
Hlf = tf(num,den);

% quick plot
bode(Hlf); grid;

% focused plot
Frange = linspace(0,30000,1000000);
[Ylfmag,Ylfph] = bode(Hlf, 2*pi*Frange);
Ylfmag = reshape(Ylfmag,max(size(Frange)),1);
Frange = Frange';
figure;plot(Frange, 20*log10(Ylfmag));grid;
title('close-up frequency response');


