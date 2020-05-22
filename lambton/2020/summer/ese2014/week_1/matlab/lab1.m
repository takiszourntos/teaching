%%
% introduction to Matlab
%
% ESE2014
%
% author: Takis Zourntos
%
% Copyright (C) 2020
%

%% Lab Manual Week 1

clear;
clc;
close all;

% 1. create a vector:
    
    % here is a row vector:
    x_row = [1 2 3 4 5];
    
    % here is a column vector:
    x_col = [1; 2; 3; 4; 5];
    
    % create vectors using:
    %    ones()
    %    zeros()
    %    rand()
    %    randn()
    %
    %    use "help <function>" at the prompt to learn more
    %    about any of these!
    %
    
    x_ones = ones(6,1); % column vector of ones
    x_zeros = zeros(1,7); % row vector of zeros
    x_rand = rand(1,8); % uniformly-distributed pseudorandom row vector of ones
    x_randn = randn(5,1); % normally-distributed pseudorandom column vector of ones
    
% 2. create a matrix:

    % note: a vector is also a matrix, nevertheless, we get what the 
    %       question means (i.e., more than 1 row or column!)
    
    A_23 = [1 2 3; 4 5 6]; % a 2x3 matrix
    A_32 = [1 2; 3 4; 5 6]; % a 3x2 matrix
    A_33 = rand(3,3); % a random (square) 3x3 matrix
    A_zeros = zeros(5,6); % a 5 x 6 matrix of zeros
    A_ones = ones(4,3); % a 4 x 3 matrix of ones
    A_identity = eye(4); % the 4x4 Identity Matrix
    
% 3. create a 5x1 vector of zeros and a 1x5 vector of random numbers:

    v_51_z = zeros(5,1);
    v_15_r = rand(1,5);
    
% 4. transpose a matrix:
    A_32_tc = A_32'; % take the complex-conjugate transpose
    A_32_t = transpose(A_32); % perform the transpose without complex conjugation
    A_32_t2 = A_32.'; % same as using transpose() function
    
% 5. compute the inner product of two vectors, the cross product of two
% vectors and find the inverse of a matrix:
    p_dot = dot(x_col, v_15_r'); % take the dot product of x_col and v_15_r'
    p_cross = cross(A_23(1,:), A_23(2,:)); % take the cross product between the two rows of A_23
    A_33_inverse = inv(A_33); % get inverse of A_33;
    P_identity = A_33*A_33_inverse; % check that this is close to identity
    A_error = eye(3) - P_identity;
    err=norm(A_error); % quantify the error
    
% 6. compute the element-wise multiplication of a matrix and a scalar:
    alpha = 0.678432; % a scalar quantity
    A_scaled = alpha*A_33; % simple asterisk does the scalar multiplication
    
% 7. concatenate two matrices:
    A_35 = [A_33  A_32]; % side-by-side concatenation
    A_53 = [A_33; A_23]; % top-bottom concatenation
    
% 8. create a vector of complex numbers:
    v_cmplx_61 = rand(6,1) + j*rand(6,1); % engineers use "j" not "i" for sqrt(-1) !!
    
% 9. multiply a row of a matrix with an element of that same matrix:
    v_9 = A_33(3,3)*A_33(2,:); % multiply second row of A_33 by the element (3,3) of the same matrix
    
% 10. generate a vector of values ranging from 0 t0 500 with 100 elements
    vrange_500 = linspace(0, 500, 100); % a linear range
    vrange_alt = 0:5:500; % another way (but it has 101 elements)
    vrange_alt_2 = 0:(500/99):500; % this is equivalent to vrange_500
    
% 11. Create a 2D plot of the sine function between 0 and 2\pi
    T0 = 2*pi; % desired period of sine (we've set this to have just one period on 0 to 2*pi)
    f0 = 1/T0; % frequency in Hz is just the reciprocal of the period
    Npts = 1024; % number of points to plot
    delta = T0/Npts; % increment or "sampling period"
    trange = 0:delta:(T0-delta);
    y_sine = sin(2*pi*f0*trange); 
    figure;plot(trange, y_sine); grid;
    
% 12. create a surface plot of the exponential function, Z = exp(x)*exp(-y):
%  note that the question did not uniquely identify the exponential
%  function in two variables, so you are free to choose it!
    Nplot = 100; % plot will be Nplot points by Nplot points
    xrange = linspace(1, -1, Nplot); % ordering is important here 
    yrange = linspace(-1, 1, Nplot);
    xvals = exp(xrange); 
    yvals = exp(-yrange);
    zvals = xvals' * yvals; % generate a table of values Nplot x Nplot in size
    figure;surf(xrange, yrange, zvals);xlabel('X');ylabel('Y'); % verify that max occurs at X=+1, Y=-1
    
% 13. generate a plot of a vector of random data; draw a horizontal line at the mean
    Ndata_pts = 512; % number of data points
    xdata = 0:(Ndata_pts-1); % independent variable
    bias = 3.789*ones(size(xdata));
    ydata = bias + randn(1,Ndata_pts); % random data with a bias term (normally distributed)
    mean_val = mean(ydata);
    figure;plot(xdata, ydata,'g.',xdata,mean_val*ones(size(xdata)),'r-',xdata,bias,'b--');
    grid
    legend('data','mean value','bias');
    
% 14. write a script that calculates the mean of five samples of data from
% a vector of random data. Calculate the overall mean. Use a for-loop to
% perform the calculations. For each iteration of the loop, use an if-else
% control statement to display whether the sample is less than, greater
% than, or equal to the mean (use data from question 13.)
    % generate five random samples
    IMAX = max(size(ydata));
    samples = zeros(5, 1);
    for ii=1:5
        indx = randi(IMAX);
        samples(ii) = ydata(indx);
    end;
    mean_samples = mean(samples);
    
    for ii=1:Ndata_pts
        if ydata(ii) > mean_samples
            disp('greater than');
        elseif ydata(ii) < mean_samples
            disp('less than');
        else 
            disp('equal to!');
        end;
    end;

% 15. create a function that calculates the sum of an arbitrary number of
% sinusoidal terms; call this function from this script--- NOTE: the
% function addsines.m is located in this directory; the function addsines
% is called as addsines(Y) where the vector Y is an Nterms x Npts matrix, 
% such that each row corresponds to a sinusoidal function;
    % note: we'll use Npts and trange defined in question 11;
    Nterms = 5;
    
    Y = zeros(Nterms, Npts); % initialize Y
    % generate Nterms random sinusoids and populate Y
    for ii = 1:Nterms;
        frandom = f0*randi(16); % frequency can be up to 16x f0;
        prandom = 2*pi*rand(1,1); % random phase shift from 0 to 2*pi
        y_sine = sin(2*pi*frandom*trange + prandom);
        Y(ii,:) = y_sine;
    end;
    
    Ytotal = addsines(Y);
    figure; plot(trange, Ytotal); grid; title('sum of sinusoids');
    