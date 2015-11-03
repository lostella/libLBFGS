function dir = lbfgs(S, Y, YS, g, idx, mem)
% dir = LBFGS(S, Y, YS, g, idx, mem)
%
%   S, an n-times-mem matrix
%   Y, an n-times-mem matrix
%   YS, a vector of length mem
%   g, a vector of length n
%   idx, a 32 bit integer (use int32(var) when passing integer var here)
%   mem, a 32 bit integer (use int32(var) when passing integer var here)
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
