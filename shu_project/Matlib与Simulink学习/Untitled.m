clear
clc

A1 = 0.8;
A2 = 1;



% plot_s_t(0.8,1);
plot_s_t(-4,1);


function plot_s_t(A1,A2)
    t = 0:0.06:6;
    w1 = 5;
    w2 = 10;
    % 实值函数
    x_t = A1*cos(w1*t) + A2*cos(w2*t);
    % 解析函数
    s_t = hilbert(x_t);
    % 瞬时相位
    inst_phase = unwrap(angle(s_t));
    % IF
    inst_frequency = diff(inst_phase)/0.06;
    % Draw
    plot(t(1:end-1),inst_frequency);
    xlim([0,6]);
    xlabel("t(s)");
    ylabel("IF(rad/s)");
end



