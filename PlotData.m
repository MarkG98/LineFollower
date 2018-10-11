% data for the left wheel
subplot(1,2,1)
x = time(1:200)/1000;
y1 = left_val(1:200);
y2 = leftspeed(1:200);
[hAx,hLine1,hLine2] = plotyy(x,y1,x,y2);

title('Left Wheel Speed and Sensor Data Over Time')
xlabel('Time (s)')

ylabel(hAx(2),'Left PWM Signal') 
ylabel(hAx(1),'Left Sensor Raw Value') 

% data for the right wheel
subplot(1,2,2)
x = time(1:200)/1000;
y1 = right_val(1:200);
y2 = rightspeed(1:200);
[hAx1,hLine3,hLine4] = plotyy(x,y1,x,y2);

title('Right Wheel Speed and Sensor Data Over Time')
xlabel('Time (s)')

ylabel(hAx1(2),'Right PWM Signal')
ylabel(hAx1(1),'Right Sensor Raw Value')