%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Discrete-Time Filter Plotter with Specs
%
%   Copyright (C) 2020 emad studio, inc.
%       author: T. Zourntos
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [] = dt_filt_plotter(num, den, Rp, Rs, Fpass, Fstop, Fs, ...
                                filt_label)

    % establish specs
    spec_pbr_pos = 1; % upper ripple limit as a unitless quantity
    spec_pbr_neg = 10^(-Rp/20); % lower ripple limit as a unitless quantity
    spec_sba = 10^(-Rs/20); % stopband attenuation, converted from dB
    wrange = linspace(0,pi,2^16); % linear frequency range for plotting
    frange = (1/(2*pi))*wrange;
    Ypbrpos = spec_pbr_pos*ones(size(wrange));
    Ypbrneg = spec_pbr_neg*ones(size(wrange));
    Ysba = spec_sba*ones(size(wrange));

    % get the frequency response
    Y = freqz(num, den, wrange);
    Y_mag = abs(Y);
    Y_ph = angle(Y);
    Y_mag=reshape(Y_mag,[1 max(size(Y_mag))]);
    Y_ph=reshape(Y_ph,[1 max(size(Y_ph))]);

    % plot response with specs superimposed
    figure; plot(frange, 20*log10(Y_mag)); grid;
    title(filt_label);
    xlabel('freq (normalized Hz)');
    ylabel('response (dB)');
    
    % plot specs/constraints for comparison
    hold on; plot(frange,20*log10(Ypbrpos),'r-', ...
        frange,20*log10(Ypbrneg),'r-',frange,20*log10(Ysba),'r-');
    xline(Fpass/Fs,'r-'); xline(Fstop/Fs,'r-');
    
    % inspect phase response
    figure; plot(frange, Y_ph); grid;
    title(strcat(filt_label, ' (Phase)'));
    xlabel('freq (normalized Hz)');
    ylabel('phase (rad)');
    hold on; xline(Fpass/Fs,'r-'); xline(Fstop/Fs,'r-');


% end dt_filt_plotter()