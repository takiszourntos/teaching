%
% for reference: Chebyshev Type I denominator roots:
%
%    1.0e+04 *
%   -0.2169 + 9.9201i
%   -0.2169 - 9.9201i
%   -0.6178 + 8.4098i
%   -0.6178 - 8.4098i
%   -0.9245 + 5.6193i
%   -0.9245 - 5.6193i
%   -1.0906 + 1.9732i
%   -1.0906 - 1.9732i
%
%
% testing our gain Sallen-Key filter parameters (third version)
%
% T. Zourntos (C) 2019 emad studio, inc.
%

clear;
close all;
clc;

%% provide pole location, p1,2 = -a +/- jb, a,b > 0
aconst = -0.2169e04;
bconst = 9.9201e04;

% thus we have alpha and beta parameters:
alpha_true = 1/(aconst^2 + bconst^2);
beta_true = -2*aconst/(aconst^2 + bconst^2);

%% design pick RC, n
%   reference denominator polynomial:
    denref = poly([aconst+j*bconst aconst-j*bconst]);
    scaling = 1/max(denref);
    denref = denref*scaling;
    
    alpha0 = denref(1);
    beta0 = denref(2);
    omega0 = sqrt(1/alpha0);
    Q0 = 1/(omega0*beta0);
    
    n = 1; % pick this way
    m = 1/((2*Q0)^2); % then m must be this
    
    % circuit parameters
    R = 50e3; % pick this one
    R1 = R;
    R3 = R;
    C4 = 1/(2*omega0*R1*Q0); 
    C2 = C4/m;

    % gain
    K = 1 + (C4*(R3+R1) - beta0)/(R1*C2);
    
    % check:
    alpha_test = R1*R3*C2*C4;
    beta_test = (1-K)*R1*C2 + C4*(R1+R3);
    denH = [alpha_test beta_test 1];
    numH = [0 0 K];
    Htest = tf(numH,denH);
    roots(denH)

