function drive(port)

pinRightForward = 9;
pinRightReverse = 10;
pinRightSpeed = 11;

pinLeftForward = 3;
pinLeftReverse = 4;
pinLeftSpeed = 5;

rightSpeed = 255;
leftSpeed = 255;

a = arduino(port);

a.pinMode(pinLeftForward,'output');
a.pinMode(pinLeftReverse,'output');
a.pinMode(pinLeftSpeed,'output');
a.pinMode(pinRightForward,'output');
a.pinMode(pinRightReverse,'output');
a.pinMode(pinRightSpeed,'output');

stop;

a.analogWrite(pinLeftSpeed,255);
a.analogWrite(pinRightSpeed,255);
  
moveForward(10);
moveReverse(5);
turnRight(2);
turnLeft(2);
stop;

clear a;

    function moveForward(time)
        a.digitalWrite(pinLeftReverse,0);
        a.digitalWrite(pinRightReverse,0);        
        a.digitalWrite(pinLeftForward,1);
        a.digitalWrite(pinRightForward,1);
        pause(time);
    end

    function moveReverse(time)
        a.digitalWrite(pinLeftForward,0); 
        a.digitalWrite(pinRightForward,0);
        a.digitalWrite(pinLeftReverse,1);
        a.digitalWrite(pinRightReverse,1);
        pause(time);
    end

    function turnRight(time)
        a.digitalWrite(pinLeftReverse,0);
        a.digitalWrite(pinRightReverse,0);
        a.digitalWrite(pinRightForward,0);
        a.digitalWrite(pinLeftForward,1);        
        pause(time);
    end

    function turnLeft(time)
        a.digitalWrite(pinLeftReverse,0);
        a.digitalWrite(pinLeftForward,0);
        a.digitalWrite(pinRightReverse,0);
        a.digitalWrite(pinRightForward,1);
        pause(time);
    end

    function stop
        a.digitalWrite(pinLeftReverse,0);
        a.digitalWrite(pinLeftForward,0);
        a.digitalWrite(pinRightReverse,0);
        a.digitalWrite(pinRightForward,0);
    end

end