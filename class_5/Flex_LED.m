% Close all figure windows
close all;
clear all;

% Create an object to connect to Arduino board
% !!! You'll have to change this to your COM port
a = arduino('COM12');

lights = [10 9 6 5 3];

for light = lights
    pinMode(a,light,'output');
end

for iLoop = 1:100
    flex = analogRead(a,0);
    
    digitalWrite(a,lights(1),double(flex > 680));
    digitalWrite(a,lights(2),double(flex > 708));
    digitalWrite(a,lights(3),double(flex > 735));
    digitalWrite(a,lights(4),double(flex > 762));
    digitalWrite(a,lights(5),double(flex > 790));
    
    pause(.1);
end
