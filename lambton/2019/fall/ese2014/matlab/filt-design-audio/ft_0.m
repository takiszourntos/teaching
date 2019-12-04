%
%
% testing our gain Sallen-Key filter parameters (second version)
%
%

clear;
close all;

C2 = 100e-9; C4 = 0.5*C2;
R1 = 55e3; R3 = 75e3;

K = linspace(1,5,100);
alpha0 = R1*R3*C2*C4;
beta0 = (1-K)*R1*C2 + C4*(R1+R3).*ones(size(K));
y = 4 * ones(size(K))*alpha0 - beta0 .^ 2;

plot(K,y);grid;

%% little more in-depth
%
% Chebyshev Type I roots:
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
a = 1.0e4*(-0.2169);
b = 1.0e4*(9.9201);
alpha1 = 1/(a^2+b^2);
beta1 = sqrt((4*alpha1)*(1-alpha1*b^2));

%
% components:
%
%   R3 = n R1 = n R;
%   C4 = m C2 = m C;
%
%
n = 2; m=3;
C = 100e-9;
R = sqrt(alpha1/(n*m*C^2));

