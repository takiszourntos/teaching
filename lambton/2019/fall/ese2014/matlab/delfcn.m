%%
%
% function returns a delta function over the domain (given by range)
% which must include 0.
%
% user supplies the "shift" parameter where the delta function is non-zero
%
function [vec] = delfcn(shift, range)
    
    % establish zero locatiom
    leftlim     = range(1); % left limit of range
    rightlim    = range(length(range)); % right limit of range
    if ((leftlim <= 0) && (rightlim >= 0))
        zeroindex = -leftlim + 1;
    else
        disp('error: range must include zero');
        return; % leave function early
    end;
    vec=zeros(size(range)); % initialize to all zero
    vec(zeroindex+shift)=1; % set the function to 1, corresponding to shift