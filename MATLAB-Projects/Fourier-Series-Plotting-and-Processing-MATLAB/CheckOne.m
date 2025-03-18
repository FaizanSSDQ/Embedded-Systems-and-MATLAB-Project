sqrt(-1);  %For Complex Number
a=2;         %Starting Point of Period
b=-2;        %Ending Point of Period   
T=b-a;       %Total Time Period   
tol=1.e-5    %Total Integral Tolerance   
N=33        %Total Number of Co-Efficients
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
wt2=D(13)*exp(j*1*2*pi*Fi*t)
wt3=D(14)*exp(j*2*2*pi*Fi*t)
wt4=D(15)*exp(j*3*2*pi*Fi*t)
wt5=D(16)*exp(j*4*2*pi*Fi*t)
wt6=D(17)*exp(j*5*2*pi*Fi*t)
wt7=D(18)*exp(j*6*2*pi*Fi*t)
wt8=D(19)*exp(j*7*2*pi*Fi*t)
wt9=D(20)*exp(j*8*2*pi*Fi*t)
wt10=D(21)*exp(j*9*2*pi*Fi*t)
wt11=D(22)*exp(j*10*2*pi*Fi*t)
wt12=D(23)*exp(j*11*2*pi*Fi*t)



wt_=D(11)*exp(j*(-1)*2*pi*Fi*t)
wt2_=D(10)*exp(j*(-2)*2*pi*Fi*t)
wt3_=D(9)*exp(j*(-3)*2*pi*Fi*t)
wt4_=D(8)*exp(j*(-4)*2*pi*Fi*t)
wt5_=D(7)*exp(j*(-5)*2*pi*Fi*t)
wt6_=D(6)*exp(j*(-6)*2*pi*Fi*t)
wt7_=D(5)*exp(j*(-7)*2*pi*Fi*t)
wt8_=D(4)*exp(j*(-8)*2*pi*Fi*t)
wt9_=D(3)*exp(j*(-9)*2*pi*Fi*t)
wt10_=D(2)*exp(j*(-10)*2*pi*Fi*t)
wt11_=D(1)*exp(j*(-11)*2*pi*Fi*t)


wtS=wt+wt2+wt3+wt4+wt5+wt6+wt7+wt8+wt9+wt10+wt11+wt12+wt_+wt2_+wt3_+wt4_+wt5_+wt6_+wt7_+wt8_+wt9_+wt10_+wt11_
wtSS=abs(wtPos)+abs(wtNeg)
plot( t , wtSS)

