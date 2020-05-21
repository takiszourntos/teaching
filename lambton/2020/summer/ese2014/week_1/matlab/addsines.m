% this function assume the passed parameter corresponds to a set of 
% sinusoidal functions (one function per row);
% it adds up the functions term by term

function Ysum = addsines(Y)

Ysum = sum(Y, 1);