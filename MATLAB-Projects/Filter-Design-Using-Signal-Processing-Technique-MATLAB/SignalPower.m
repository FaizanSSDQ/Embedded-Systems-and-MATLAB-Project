%Periodic Signal and Signal Power
Dt=0.002  %Sample of interval
T=6 %Period of the signal
M=3  %To generate 2M periods
t=[0*:Dt:T-Dt]
%Then evaluate signal over the range of T
y=exp(-abs(t/2)).*sin(2*pi*t).*(uStep(t)-uStep(t-4));
time=[];
y_period=[];
for i=-M:M-1
time=[time i*T+t];
y_period=[y_period y];
end
figure(1)
plot(time , y_period)
axis([-8 8 -2 2])
%Signal power is of a periodic signal
s_power=sum(y_period*y_period')*Dt/(max(time)-min(time))

%Signal energy is only for Aperiodic signal
s_energy=sum(y.*conj(y))*Dt










