j=sqrt(-1);  %For Complex Number
a=2;         %Starting Point of Period
b=-2;        %Ending Point of Period   
T=b-a;       %Total Time Period   
tol=1.e-5    %Total Integral Tolerance   
N=7        %Total Number of Co-Efficients
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


%Re-Making the lost function
t=-5:1:5
y=Triangle(t/2)*1.5
wtS=0;
for i=-N:N
    wtM=(D(i+N+1))*exp(j*2*pi*Fi*t*i)
    wtS=wtS+(wtM)
end
wtT=abs(wtS)
plot(t , wtT , t , y)
legend('triangle(t/6)' , 'wt(t)')
ylabel('y=triangle(t/2)')
xlabel('t (1)')

title('w(t) for N=17 Coefficients')
grid on 






%plot(t , store)