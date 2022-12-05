clear
clc

k_1 = -10:1:10;
k_2 = -50:1:50;
k_3 = -100:1:100;
k_4 = -100:1:100;

t = 0:0.01:5;
T = 1;

f_1 = 0;
f_2 = 0;
f_3 = 0;

for i = 1 : length(k_1)
    f_1 = f_1 + exp(1i*k_1(i)*(2*pi/T).*t);
end

for i = 1 : length(k_2)
    f_2 = f_2 + exp(1i*k_2(i)*(2*pi/T).*t);
end

for i = 1 : length(k_3)
    f_3 = f_3 + exp(1i*k_3(i)*(2*pi/T).*t);
end

subplot(221);
plot(t,f_1);
title("n = -10~10");
grid on;
xlabel("Time");
ylabel("Function");

subplot(222);
plot(t,f_2);
title("n = -50~50");
grid on;
xlabel("Time");
ylabel("Function");

subplot(223);
plot(t,f_3);
title("n = -100~100");
grid on;
xlabel("Time");
ylabel("Function");

subplot(224);
plot(t,f_1);
hold on;
plot(t,f_2);
plot(t,f_3);
title("All in all");
grid on;
xlabel("Time");
ylabel("Function");
legend("n=10","n=50","n=100");

