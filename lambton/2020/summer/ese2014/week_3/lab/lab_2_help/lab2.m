%%
% main script corresponding to Lab 2 (partial solutions)
%
% Copyleft (C) 2019 T. Zourntos (emad studio inc.)
%

%% initialize
clear all;
close all;
clc;

%% problem 1
nr = -5:15;
x = 3*delfcn(-2,nr)+2*delfcn(0,nr)-delfcn(3,nr)+5*delfcn(7,nr);

figure;stem(nr,x);grid;
