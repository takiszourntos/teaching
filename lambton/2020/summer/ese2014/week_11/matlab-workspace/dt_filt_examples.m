%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
%   various DT filter design examples
%   
%   Copyright (C) 2020 emad studio, inc.
%       author: T. Zourntos
%
%   filter specs: 
%       Rp = 1 dB
%       Rs = 80 dB
%       Fpass = 18.5 kHz
%       Fstop = 24 kHz
%       Fs = 200 kHz
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%
% prepare workspace
%
close all;
clear;
clc;

%
% filter spec parameters
%
Rp = 1;
Rs = 80;
Fpass = 18500;
Fstop = 24000;
Fs = 200e3;
Ws = 2*pi*Fs;
Ts = 1/Fs;

%
% FIR design (coefficients found using filtdesigner app)
%
% realization is fairly straightforward: a tapped-delay line
%
load num_fir; % check the min and max values of these coefficients
Hfir = tf(num_fir, 1, Ts);
Hfir_ss = ss(Hfir);
filt_label = 'FIR filter design (N=93)';
dt_filt_plotter(num_fir, 1, Rp, Rs, Fpass, Fstop, Fs, filt_label);

%
% IIR design -- Butterworth
%
[num_bw, den_bw] = butter(27, 1.95*Fpass/Fs);
H_bw = tf(num_bw, den_bw, Ts);
H_bw_ss = ss(H_bw);
filt_label = 'IIR Butterworth filter design';
dt_filt_plotter(num_bw, den_bw, Rp, Rs, Fpass, Fstop, Fs, filt_label);

%
% IIR design -- Elliptical
%
[num_e, den_e] = ellip(8, Rp, Rs, 2.0*Fpass/Fs);
H_e = tf(num_e, den_e, Ts);
H_e_ss = ss(H_e);
filt_label = 'IIR Elliptical filter design';
dt_filt_plotter(num_e, den_e, Rp, Rs, Fpass, Fstop, Fs, filt_label);



































