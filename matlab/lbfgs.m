function dir = lbfgs(S, Y, YS, H0, g, idx, currmem)
% dir = LBFGS(S, Y, YS, g, idx, mem)
%
%   S, an n-times-mem matrix
%   Y, an n-times-mem matrix
%   YS, a vector of length mem
%	H0, a positive real number
%   g, a vector of length n
%   idx, a 32 bit integer (use int32(var) when passing integer var here)
%   currmem, a 32 bit integer (use int32(var) when passing integer var here)
%
% Computes the L-BFGS direction associated with
% gradient g and mem pairs (s, y), where
% s are columns of S and y are columns of Y, taken
% starting from column idx and proceeding circularly
% backwards. Vector YS contains the inner products
% <y, s> of correspondent columns of Y and S.
%
% The circular access to matrices S and Y is adopted
% so that no memcpy operation is needed every time
% the matrices are full and new columns need to be
% stored.

maxmem = size(S, 2);
alpha = zeros(1, maxmem);
q = g;
curridx = idx;
for i = 0:(currmem-1)
    alpha(curridx) = (S(:,curridx)'*q)/YS(curridx);
    q = q - alpha(curridx)*Y(:,curridx);
    curridx = curridx-1;
    if curridx == 0, curridx = maxmem; end
end
r = H0*q;
for i = 0:(currmem-1)
    curridx = curridx+1;
    if curridx > maxmem, curridx = 1; end
    beta = (Y(:,curridx)'*r)/YS(curridx);
    r = r + (alpha(curridx)-beta)*S(:,curridx);
end
dir = r;
