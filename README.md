# GK_BoyBoy_ScrollingCanvas
Arduino program for SparkFun ProDriver (TC78H670FTG). 

Behavior:
    Continously moves stepper motor between two positions.

Optional:
    Button 1: Calibrate motor position...
        - sets 'start-postion' to the current step postion 
        - reverses motor direction (rotation)
        - pause movement before continuing stepper loop
    Button 2: Pause movement for a specified length of time (ms)
