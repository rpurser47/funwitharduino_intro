% Create an object to connect to Arduino board
a = arduino('COM8');

% Define pins 9,10 and 11 as output pins for our RGB LED
a.pinMode(9,'output');
a.pinMode(10,'output');
a.pinMode(11,'output');

% Define the lowest and highest FSR readings along with color range
lowestFSR = 120;
highestFSR = 1023;

for iLoop = 1:1000
    data = analogRead(a,0);
    
    % Min-Max normalization
    greenLEDValue = floor((data - lowestFSR)/(highestFSR-lowestFSR)*255);
    redLEDValue = 255 - greenLEDValue;
    blueLEDValue = 0;
    
    % Write values to the LED
    a.analogWrite(9,redLEDValue);
    a.analogWrite(10,greenLEDValue);
    a.analogWrite(11,blueLEDValue);
end

clear a;