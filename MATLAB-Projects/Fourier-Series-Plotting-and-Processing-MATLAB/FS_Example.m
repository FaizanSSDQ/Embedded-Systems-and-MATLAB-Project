j=sqrt(-1);  %For Complex Number
a=2;         %Starting Point of Period
b=-2;        %Ending Point of Period   
T=b-a;       %Total Time Period   
tol=1.e-5    %Total Integral Tolerance   
N=11         %Total Number of Co-Efficients
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
    
subplot(211)
s1=stem([-N:N] , abs(D));
set(s1 , 'Linewidth' , 2);
ylabel('|{\it D}_{it n}|');
title('Amplitude of {\it D}_{\it n}');
grid on


subplot(212)
s2=stem([-N:N] , angle(D));
set(s2 , 'Linewidth' , 2);
ylabel('<{\it D}_{\it_n}')
title('Angle of {\it D}_{\it n}')
grid on











