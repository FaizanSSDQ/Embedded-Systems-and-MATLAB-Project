t=linspace(-60 , 60 , 600)
y=UnitStep(t-20)-UnitStep(t-40)
plot(t , y)
axis([-20 20 -2 2 ])
grid on