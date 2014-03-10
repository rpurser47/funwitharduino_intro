% Close all figure windows
close all;
clear all;

% Create an object to connect to Arduino board
a = arduino('COM8');

% Create figure window
figureHandle = figure('Name','Force Sensor Readings');

% Create axes
axesHandle = axes('Parent',figureHandle);

ylim(axesHandle,[130 1100]);
box(axesHandle,'on');
hold(axesHandle,'all');

% Create title
title('Force Sensor Readings');

% Create xlabel
xlabel('Time');

% Create ylabel
ylabel('FSR Readings');


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