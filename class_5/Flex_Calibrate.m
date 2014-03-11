% The resistance of an unbent Flex sensor is 25K ohms (from datasheet): 
% https://www.sparkfun.com/datasheets/Sensors/Flex/flex22.pdf
%
% The circuit uses another 10K ohms in series with a 5V supply.
% So, the current flowing through our circuit, with flex sensor unbent:
%
% V = IR;
% 5 = I x (10K + 25K);
% I = 5/35K;
% I = 0.143mA
%
% With that much current, the voltage across our unbent flex sensor:
%
% V = IR;
% V = 0.143mA x 25K
% V = 0.143 x 25
% V = 3.575V
%
% The digital value for that unbent flex sensor should be:
%
% (1023*3.575)/5
% 731.445
% ~732

% Close all figure windows
close all;
clear all;

% Create an object to connect to Arduino board
% !!! You'll have to change this to your COM port
a = arduino('COM12');

% Initialize Calibration values.  Start with the max reading slightly
% higher than the min reading, or interp1 will complain
zeroDegreeValue = analogRead(a,0);
ninetyDegreeValue = zeroDegreeValue + 1;

disp('Please bend sensor through its complete range....')

for iLoop = 1:100
    % Read in the raw value
    rawValue = analogRead(a,0);
    
    if(zeroDegreeValue > rawValue)
        zeroDegreeValue = rawValue;
    end
    
    if(ninetyDegreeValue < rawValue)
        ninetyDegreeValue = rawValue;
    end
    
    angle = interp1([zeroDegreeValue ninetyDegreeValue],[0 90],rawValue);
    
    disp([num2str(rawValue) ' -> ' num2str(angle) ' degrees']); 
    pause(.25);
end
disp(char(10));  % Produces a blank line
disp('Copy this -- you''ll need it for the next exercise');
disp(['calibration = [ ' num2str([zeroDegreeValue ninetyDegreeValue]) ' ];']);
