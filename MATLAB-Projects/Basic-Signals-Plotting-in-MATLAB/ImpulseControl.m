%t=linspace(-20 , 20 , 20)
t=-10:1:500
Im=UnitImpulse(t)
plot(t , Im)
axis([-10 500 -4 4])
grid on