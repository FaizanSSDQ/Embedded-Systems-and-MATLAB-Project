B=4;
f0=1/4;
T0=1/f0;
Ts=1/(2*B);
N0=T0/Ts
k=0:(N0-1);
k=k'

for m=1:length(k)
    if k(m)>=0 & k(m)<=3, gk(m)=1
    end
    
    if k(m)==4 & k(m)==28   , gk(m)=0.5;
    end
    
    if (k(m)>=5  & k(m)<=27) , gk(m)=0
    end
    
    if (k(m)>=29  & k(m)<=31) , gk(m)=1
    end
end
gk=gk'
Gr=fft(gk)


q=0:N0-1;
q=q'
for m=length(q)
    if q(m)>=0 & q(m)<=7 , Hq(m)=1
    end
    
    if q(m)==8 & q(m)==24 , Hq(m)=0.5
    end
    
    if q(m)>=9 & q(m)<=23 , Hq(m)=0
    end
    
    if q(m)>=25 & q(m)<=31 , Hq(m)=2
    end
    
    
end



Hq=Hq'
HHq=Gr.*Hq
yH=ifft(HHq)
plot(q , yH)
%subplot(221)
%stem(k , gk)
%title("Rectangle Pulse")
%subplot(222)
%stem(q , Hq)
%title("Filter Pass Signal")
%subplot(223)
%stem(k , Gr)
%title("Fourier Transform of Original Signal")
%subplot(224)
%stem(k , yQ)
%title("Fourioer Transform of filtered Signal")
