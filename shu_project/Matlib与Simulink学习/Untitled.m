clear
clc

M = 20;
N = 12;
K = M + N + 1;

w = -pi : pi/2000 :pi;

H_jw = (1/K)*exp(1i*w*((N-M)/2)).*sin(w*(K/2))./sin(w/2);

plot(w,abs(H_jw));
xlabel("w");
ylabel("H(e^{jw})");
xlim([-pi pi]);

