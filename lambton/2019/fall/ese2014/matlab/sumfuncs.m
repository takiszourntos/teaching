function [s]=sumfuncs(Y)
% sum up the rows (individual functions) of Y
sizeY  = size(Y); % get rows x cols of Y
nrowsY = sizeY(1);
ncolsY = sizeY(2);

s=zeros(1, ncolsY);
for ii=1:nrowsY
    s(1, :) = s(1, :) + Y(ii, :);
end;

% % slow way
% for ii=1:nrowsY
%     for jj = 1:ncolsY
%         s(1, jj) = s(1, jj) + Y(ii, jj);
%     end;
% end;
