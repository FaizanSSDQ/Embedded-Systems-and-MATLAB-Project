	clear all
	j=sqrt(-1);	% Define j for complex algebra
	b=2; a=-2; 	% Determine one signal period 
	T=b-a;  	% length of the period
	N=11;		% Number of FS coefficients
			% on each side of zero frequency
	% now calculate D_0 and store it in D(N+1);
	Func= @(t) triangle(t/2);
	D(N+1)=1/T*integral(Func,a,b);	% Using quad.m integration
for i=1:N
% Calculate Dn for n=1,...,N (stored in D(N+2) ... D(2N+1)
	Func= @(t) exp(-j*2*pi*t*i/T).*triangle(t/2);
	D(i+N+1)=1/T*integral(Func,a,b);
% Calculate Dn for n=-N,...,-1 (stored in D(1) ... D(N)
	Func= @(t) exp(j*2*pi*t*(N+1-i)/T).*triangle(t/2);
	D(i)= 1/T*integral(Func,a,b);
end
figure(1);
subplot(211);s1=stem([-N:N],abs(D));
set(s1,'Linewidth',2); ylabel('|{\it D}_{\it n}|');
title('Amplitude of {\it D}_{\it n}')
subplot(212);s2=stem([-N:N],angle(D));
set(s2,'Linewidth',2); ylabel('<{\it D}_{\it n}');
title('Angle of {\it D}_{\it n}');

 n=-N:N;
 k=0;
 for t=-2:.01:2
    k=k+1;
    fapprox(k)=sum(D.*(exp(j*n*2*pi*t/T)));
 end
 t=-2:.01:2;
 %fexact=4*(t<=3)-2*(t>=3);
 figure(2);
 plot(t,fapprox,t,triangle(t/2))