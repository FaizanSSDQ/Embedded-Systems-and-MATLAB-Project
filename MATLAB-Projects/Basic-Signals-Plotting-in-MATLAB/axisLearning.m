x=linspace(-10 ,10 , 10)
y=exp(x)
y1=-exp(x)
y2=exp(-x)
y3=-exp(-x)
%plot(x , y , x , y1)
plot(x , y2 , x , y3 , x, y , x,y1)
axis([-1 1 -1 1])
legend("Faizan Saleem")

grid on 