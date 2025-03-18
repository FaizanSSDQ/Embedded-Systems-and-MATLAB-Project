t=-3:0.01:3
y=exp(-t).*sin(10*pi*t).*uStep(t+1)
figure(1)
plot(t ,y )
axis([-2 2 -4 4])
grid on