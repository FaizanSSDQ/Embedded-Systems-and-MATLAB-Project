f=-10:0.001:10


t=-5:0.1:5;
y=Rectangle(t);
%plot(t , y)
%hold on

for n=1:50
    y=sin(n*pi*f)
    y2=(y./(f*pi))
    
    stem(f , y2)
    %plot(f , y2 )
    axis([-5 5 -2 2])
    title("Fourier Transform of Rectangular Function")
    grid on
    hold on 
end