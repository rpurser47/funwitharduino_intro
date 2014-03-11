% Close all figure windows
close all;
clear all;

% Create an object to connect to Arduino board
% !!! You'll have to change this to your COM port
a = arduino('COM12');

for iLoop = 1:100
    disp(analogRead(a,0)); 
    pause(.25);
end
