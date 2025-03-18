t=-1:0.002:4
%Dummy Program
y=Rectangle(t)
y2=Rectangle(t*2)
subplot(211)
s1=stem(t , y)
set(s1 ,'Linewidth' , 2)
ylabel('|{\it D}_{\it n}|')

subplot(212)
s1=stem(t , y2)
set(s1 ,'Linewidth' , 2)
ylabel('|{\it D}_{\it n}|')