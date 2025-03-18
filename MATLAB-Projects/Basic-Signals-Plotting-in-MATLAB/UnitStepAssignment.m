t=linspace(-60 , 60 , 80)
y0=UnitStep(t)
subplot(2 , 2 , 1)
plot(t , y0)
axis([-20 20 -2 2])
grid on

y1=UnitStep(t)-UnitStep(t-10)
subplot(2 , 2 , 2)
plot(t , y1)
axis([-20 20 -2 2])
grid on

y2=(UnitStep(t-10)-UnitStep(t-20))
y4=(UnitStep(t-20)-UnitStep(t-40))
subplot(2 , 2 , 3)
plot(t , y2 , t, y4)
axis([-20 20 -2 2])
grid on


y3=UnitStep(t)-UnitStep(t-10)
subplot(2 , 2 , 4)
plot(t , y1 , t, y0)
axis([-20 20 -2 2])
grid on