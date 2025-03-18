t=linspace(-60 , 60 , 600)
y=UnitStep(t-20)-UnitStep(t-40)
y2=2*(UnitStep(t-30)-UnitStep(t-35))
plot(t , y , t, y2)
axis([-40 60 -2 2 ])
grid on