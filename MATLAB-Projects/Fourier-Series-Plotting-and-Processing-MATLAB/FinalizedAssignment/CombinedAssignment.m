sqrt(-1);  %For Complex Number
a=2;         %Starting Point of Period
b=-2;        %Ending Point of Period   
T=b-a;       %Total Time Period   
tol=1.e-5    %Total Integral Tolerance   
N=11        %Total Number of Co-Efficients
             %On each side of the zero frequency 
Fi=[-N;N]*2*pi*T
   
% D_0 coefficients
 
Func=@(t)Triangle(t/2);
D(N+1)=1/T*quad(Func , a , b , tol)

for i=1:N
    %For Frequency n=1...N
    Func=@(t) exp(-j*2*pi*t*i/T).*Triangle(t/2);
    D(i+N+1)=quad(Func , a , b , tol);
    %For Frequency n=-N...-1
    Func=@(t) exp(j*2*pi*t*(N+1-i)/T).*Triangle(t/2);
    D(i)=quad(Func , a , b , tol);
end

t=-5:0.2:5
y=Triangle(t/2)
wt0=D(12)*exp(j*0*2*pi*Fi*t)

wtPos=0;
wtNeg=0;
for i=1:N
wt_U=D(i+N+1)*exp(j*i*2*pi*Fi*t)
wtPos=wtPos+wt_U
end

for i=-N:-1
wt_U2=D(i+N+1)*exp(j*i*2*pi*Fi*t)
wtNeg=wtNeg+wt_U2
end
wtSS=(wtPos)+(wtNeg)+wt0
plot( t , wtSS , t , y)
title('Approximation of triangle(t/2) for |{\\it D}_{\it n}|')
ylabel('y=triangle(t/2)')
grid on
