clear
clc

A=imread("pixel.png");
t=graythresh(A); 
A = im2bw(A,t);
imshow(A)