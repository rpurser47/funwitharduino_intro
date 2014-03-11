function Flex_LED_Solution
    % Create an object to connect to Arduino board
    % !!! You'll have to change this to your COM port
    a = arduino('COM12');

    redPin1 = 10;
    redPin2 = 9;
    yellowPin = 6;
    greenPin1 = 5;
    greenPin2 = 3;

    % !!! You'll need to copy this calibration from running Flex_LED_Calibrate
    calibration = [ 694  820 ];

    for iLoop = 1:100
        % Code to read the raw value (using analogRead) into rawValue
        rawValue = analogRead(a,0);
        angle = interp1(calibration,[0 90],rawValue,'linear','extrap');

        % Uses mapAngleToLED function (below) to calculate the LED
        % values from the angle and write it (using analogWrite)
        % redPin1: 0-10 degrees
        analogWrite(a,redPin1, mapAngleToLED([0 10],angle));
        % redPin2: 10-40 degrees
        analogWrite(a,redPin2, mapAngleToLED([10 40],angle));
        % yellowPin: 40-50 degrees
        analogWrite(a,yellowPin, mapAngleToLED([40 50],angle));
        % greenPin1: 50-80 degrees
        analogWrite(a,greenPin1, mapAngleToLED([50 80],angle));
        % greenPin2: 80-90 degrees
        analogWrite(a,greenPin2, mapAngleToLED([80 90],angle));

        pause(.25);
    end

    function output = mapAngleToLED(angleRange, angle)
        output = floor(interp1(angleRange,[0 255],angle,'linear','extrap'));
        if output < 0
            output = 0;
        end
        if output > 255
            output = 255;
        end
       % disp(['Angle:' num2str(angle) ' Range: [' num2str(angleRange) '] Output:' num2str(output)]);
    end
end