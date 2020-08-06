%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Continuous-Time Filter Plotter with Specs
%
%   Copyright (C) 2020 emad studio, inc.
%       author: T. Zourntos
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [] = ct_filt_plotter(num, den, Rp, Rs, Fpass, Fstop, filt_label)

    % establish specs
    spec_pbr_pos = 1; % upper ripple limit as a unitless quantity
    spec_pbr_neg = 10^(-Rp/20); % lower ripple limit as a unitless quantity
    spec_sba = 10^(-Rs/20); % stopband attenuation, converted from dB

    Wrange = linspace(0,2*pi*50000,1000000);    % linear frequency range 
                                                % for plotting
    Frange = (1/(2*pi))*Wrange;
    Ypbrpos = spec_pbr_pos*ones(size(Wrange));
    Ypbrneg = spec_pbr_neg*ones(size(Wrange));
    Ysba = spec_sba*ones(size(Wrange));
    
    H0 = tf(num, den);
    [Y_mag,Y_ph] = bode(H0, Wrange);
    Y_mag=reshape(Y_mag,[1 max(size(Y_mag))]);
    Y_ph=reshape(Y_ph,[1 max(size(Y_ph))]);
    
    % plot response with specs superimposed
    figure; plot(Frange, 20*log10(Y_mag)); grid;
    title(filt_label);
    xlabel('freq (kHz)');
    ylabel('response (dB)');
    
    % plot specs/constraints for comparison
    hold on; plot(Frange,20*log10(Ypbrpos),'r-', Frange, ...
                20*log10(Ypbrneg),'r-',Frange,20*log10(Ysba),'r-');
    xline(Fpass,'r-'); xline(Fstop,'r-');
    
    % inspect phase response
    figure; plot(Frange, Y_ph); grid;
    title(strcat(filt_label, ' (Phase)'));
    xlabel('freq (kHz)');
    ylabel('phase (rad)');
    hold on; xline(Fpass,'r-'); xline(Fstop,'r-');

% end ct_filt_plotter()