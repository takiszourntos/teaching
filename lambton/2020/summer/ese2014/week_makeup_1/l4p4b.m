%
% homework help
%
% Lab 4, question 4b)
%
%
clc; clear; close all;

% create the impulse response
n_range = -20:19;
h_4b = sinc(0.2*n_range);
figure; plot(n_range, h_4b); grid;

% obtain H(e^jw)
H_4b = fft(h_4b);
size(H_4b); % confirm that H_4b has the correct number of points (40)
figure; plot(abs(H_4b));

% get symmetric plot about 0
H_4b_symm = [H_4b(21:40) H_4b(1:20)];
wrange = (pi/20)*n_range;
figure; plot(wrange,abs(H_4b_symm));
