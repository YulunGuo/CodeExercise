clear
clc

t = linspace(-2*pi,2*pi);

h_t = sqrt(2)*(sin(t) + cos(t));


plot(t,h_t);
hold on;
axis on;
plot(t,fft(h_t))
xlabel("w");
ylabel("H(e^{jw})");
xlim([-2*pi,2*pi]);
legend("h(t)","FFT(h(t))");

