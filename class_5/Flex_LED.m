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
    
    angle = interp1([680 790],[0 1],flex);
    
    digitalWrite(a,lights(1),double(angle > .05));
    digitalWrite(a,lights(2),double(angle > .25));
    digitalWrite(a,lights(3),double(angle > .50));
    digitalWrite(a,lights(4),double(angle > .75));
    digitalWrite(a,lights(5),double(angle > .95));
    
    pause(.1);
end
