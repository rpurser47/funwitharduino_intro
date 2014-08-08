function Flex_LED
    % Create an object to connect to Arduino board
    % !!! You'll have to change this to your COM port
    a = arduino('COM12');

    redPin1 = 10;
    redPin2 = 9;
    yellowPin = 6;
    greenPin1 = 5;
    greenPin2 = 3;

    % !!! You'll need to copy this calibration from running Flex_LED_Calibrate
    % calibration = [ 694  820 ];

    for iLoop = 1:100
        % !!! Add the code to read the raw value (using analogRead) into rawValue
        angle = interp1(calibration,[0 90],rawValue,'linear','extrap');

        % !!! Use the mapAngleToLED function (below) to calculate the LED
        % values from the angle and write it (using analogWrite)
        % redPin1: 0-10 degrees
        % redPin2: 10-40 degrees
        % yellowPin: 40-50 degrees
        % greenPin1: 50-80 degrees
        % greenPin2: 80-90 degrees

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