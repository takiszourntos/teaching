% this function assumes that the passed parameter corresponds to a set of 
% sinusoids (one function per row);
% the function adds up the sinusoids, point by point
% 
% author: Takis Zourntos
%
% Copyright (C) 2020
%


function Ysum = addsines(Y)

Ysum = sum(Y, 1);