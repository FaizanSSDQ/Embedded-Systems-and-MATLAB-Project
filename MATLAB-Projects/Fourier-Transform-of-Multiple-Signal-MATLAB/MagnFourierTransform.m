f=-1:0.002:1;
a=0.999
g0=(2*f*pi)
g1=a^2+(g0.^2);
g2=g1.^0.5
g3=1./g2;

%angle
A0=g0./a;
A1=-1*atan(A0)

%plot(f , g3 , f , A1)
stem(f , g3 )
axis([-5 5 -2 2 ])
grid on