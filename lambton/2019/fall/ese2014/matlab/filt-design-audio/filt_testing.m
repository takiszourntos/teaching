%
%
% testing our gain Sallen-Key filter parameters
%
%

clear;
close all;

C1 = 100e-9; C2 = 0.1*C1;
R1 = 10e3; R2 = R1;

g = linspace(1,5,100);
alpha0 = -2*((C2*R2)/(C1*R1));
beta0 = ((C2*R2)/(C1*R1))*(((C2*R2)/(C1*R1))-1);

y = g .^ 2 + alpha0 * g + beta0*ones(size(g));

plot(g,y);grid;