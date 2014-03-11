% Close all figure windows
close all;
clear all;

% Create an object to connect to Arduino board
% !!! You'll have to change this to your COM port
a = arduino('COM12');

% Create figure window
figureHandle = figure('Name','Flex Sensor Readings');

% Create axes
axesHandle = axes('Parent',figureHandle);

ylim(axesHandle,[130 1100]);
box(axesHandle,'on');
hold(axesHandle,'all');

% Create title
title('Flex Sensor Readings');

% Create xlabel
xlabel('Time');

% Create ylabel
ylabel('Flex Readings');


% Create initial plot
plot(axesHandle,0,0);

% Start collecting readings
tic;
for iLoop = 1:5000
    data(iLoop) = analogRead(a,0);  %#ok<*SAGROW>
    timeStamp(iLoop) = toc;
    plot(axesHandle,timeStamp,data,'b');
    drawnow;
end

lowestValue = min(data);
highestValue = max(data);

clear a;