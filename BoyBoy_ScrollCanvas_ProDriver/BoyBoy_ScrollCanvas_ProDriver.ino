#include "SparkFun_ProDriver_TC78H670FTG_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_ProDriver
PRODRIVER myProDriver; //Create instance of this object
//  Driver Settings
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_4 2
#define PRODRIVER_STEP_RESOLUTION_1_4 4

// constants won't change. They're used here to set pin numbers:
const int button1Pin = 10;     // the number of the pushbutton pin
const int button2Pin =  12;    // the number of the second pushbutton pin

// button variables:
int button1State = 0;         // variable for reading the pushbutton status
int button2State = 0;
// motor variables:
int startStep;
int endStep;
int stepDelay = 10;           // SPEED => milliseconds between pulses (steps)
//  Calibration Variables
int currentStep = 1;          // initial step count for "start/reset"
int currentDir = 0;           // initial direction for "start/reset"
int dirForward = 0;
int dirReverse = 1;

void setup() {
  Serial.begin (4800);
  Serial.println("Please press a button");
  myProDriver.settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_VARIABLE_1_4;
  myProDriver.begin();
  myProDriver.changeStepResolution(PRODRIVER_STEP_RESOLUTION_1_4);
  pinMode(button1Pin, INPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button2Pin, INPUT);
  startStep=1;
  endStep=8000;     //  ROTATION: 1rotation = 800steps [[ so... 20rot = 16000step ]]
}

void loop() {
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  // check if the pushbutton has not been pressed:
  if (button1State == HIGH) {
    Serial.println("short pause");
    delay(10000);
  }
  if (button2State == HIGH) {             //  Check Reset Button state
    Serial.println("reset calibration");
    currentStep = 1;                      // Reset step count
    if (currentDir == 0) {                // Redefine (invert) "Forward" & "Reverse" values;
      dirForward = 1;
      dirReverse = 0;
    } else {
      dirForward = 0;
      dirReverse = 1;
    }
    currentDir = dirForward;
    delay(1000);
  } else {
    //  Loop Directions
    if (currentStep <= endStep && currentDir == dirForward) {
      myProDriver.step(1,currentDir);   // step the motor forward one step
      delay(stepDelay);                 // SPEED Control: milliseconds between pulses
      currentStep = currentStep+1;      // count the step taken
      Serial.print(currentStep);        // print step count in serial monitor
      if (currentStep >= endStep) {     // if the motor is at the endStep change direction.
        currentDir = dirReverse;        
        delay(3000);                    
      }
    }
    if (currentStep >= startStep && currentDir == dirReverse){
      myProDriver.step(1,currentDir);   // step motor in reverse
      delay(stepDelay);                 // SPEED Control: milliseconds between pulses
      currentStep = (currentStep-1);    // count the step taken
      Serial.print(currentStep);        // print the step count in serial monitor
      if (currentStep <= startStep){    // if the motor is at the startStep change direction
        currentDir = dirForward;
        delay(3000);
      }
    }
  }
} 