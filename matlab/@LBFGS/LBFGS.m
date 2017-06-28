classdef LBFGS < handle
% LBFGS creates a limited-memory BFGS operator
%
%   H = LBFGS(n, mem) constructs a limited-memory BFGS operator over a space
%   of dimension n, with memory mem, and assigns it to H.
%
%   H.push(s, y) pushes a new pair of vectors (s, y) into the buffer.
%
%   u = H*v applies H to vector v; use -(H*v) if the minus is needed.
  properties
    n % space dimension
    mem % memory
    S, Y, YS, H0, idx, currmem
    cntskip
  end
  methods
    function obj = LBFGS(n, mem)
      obj.n = n;
      obj.mem = mem;
      obj.S = zeros(n, mem);
      obj.Y = zeros(n, mem);
      obj.YS = zeros(mem, 1);
      obj.idx = 0;
      obj.currmem = 0;
      obj.cntskip = 0;
    end
  end
end
