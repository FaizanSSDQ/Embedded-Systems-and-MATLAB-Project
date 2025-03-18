T=4  %Duration
t=[-10:0.02:10] %Range of x axis
z=rectpuls(t ,T)
plot(t , z)
X=fft(z)
%plot(t , fftshift(X))