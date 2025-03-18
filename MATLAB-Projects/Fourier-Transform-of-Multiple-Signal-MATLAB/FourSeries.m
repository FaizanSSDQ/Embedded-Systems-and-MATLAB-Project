j=sqrt(-1);
a=-2; b=2;
T=b-a;
tol=1.e-5
N=11;
Fi=[-N:N]*2*pi/T;
%Now Calculating D 0 coefficients
Func=@(t) triangle(t/2)
D(N+1)=1/T*integral(Func , a , b )
for i=1:N
    %For N=1 to 11 coefficients
    Func=@(t) exp(-j*2*pi*t*i/T).*triangle(t/2);
    D(N+i+1)=1/T*integral(Func , a , b)
    
    %For N=-11 to -1 coefficeints
    Func=@(t) exp(j*2*pi*t*(N+1-i)/T).*triangle(t/2)
    D(i)=1/T*integral(Func , a , b)
end

figure(1)
subplot(211)
s1=stem([-N:N] , abs(D))
set(s1,'Linewidth',2); ylabel('|{\it D}_{\it n}|');
title('Amplitude of {\it D}_{\it n}')
subplot(212)
stem([-N:N] , angle(D))


n=-N:N
k=0
for t=-2:0.02:2
    k=k+1
    fapprox(k)=sum(D.*exp(j*2*pi*n*t/T))
    
end
t=-2:0.02:2
figure(2)
plot(t , fapprox)





