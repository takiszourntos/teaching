%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
%   various CT filter design examples
%   
%   Copyright (C) 2020 emad studio, inc.
%       author: T. Zourntos
%
%   filter specs: 
%       Rp = 2 dB
%       Rs = 80 dB
%       Fpass = 16 kHz
%       Fstop = 20 kHz
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
Rp = 2;
Rs = 80;
Fpass = 16000;
Fstop = 20000;


%% Butterworth Design
    % design attempt
    Nbw = 43;
    Wnbw = 2*pi*16100;
    [numHbw, denHbw] = butter(Nbw,Wnbw,'s');
    
    % plot response with specs superimposed
    filt_label='Butterworth Analog Filter Response (N=43)';
    ct_filt_plotter(numHbw, denHbw, Rp, Rs, Fpass, Fstop, filt_label);
    
    
%% Elliptical Design
    % design attempt
    Ne = 8;
    Rpe = 2;
    Rse = 80;
    Wpe = 2*pi*16000;
    [numHe, denHe] = ellip(Ne,Rpe,Rse,Wpe,'s');
 
    % plot response with specs superimposed
    filt_label='Elliptical Analog Filter Response (N=8)';
    ct_filt_plotter(numHe, denHe, Rp, Rs, Fpass, Fstop, filt_label);
%%
