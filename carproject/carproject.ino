//hi
//modes to see which way the car should go
#define GO_BACK 0
#define END_MAZE 1
#define GO_RIGHT 2
#define GO_LEFT 3
#define GO_STRAIGHT 4
#define FINISHED 5

//pins for sensors
#define trigPin1 A1 // Left
#define echoPin1 A2
#define trigPin2 A5 // Center
#define echoPin2 7
#define trigPin3 A3 // Right
#define echoPin3 A4

//pins for buttons
#define buttonPin 1

//Initializing variables for sensors
long duration, distance, RightSensor,FrontSensor,LeftSensor;

//Pins for Motor
#define MotorPinA 12 // for motor A direction, high is CW and low is CCW
#define MotorSpeedPinA 3 // Pin that controls speed for motor A
#define MotorBrakePinA 9 // Pin that controls brake for motor A
#define MotorPinB 13 // for motor B direction, high is CW and low is CCW
#define MotorSpeedPinB 11// Pin that controls speed for motor B
#define MotorBrakePinB 8// Pin that controls speed for motor B

//Turning variables
#define CW  HIGH
#define CCW LOW

//constants
#define runExtraInchConst 1000
#define runExtraInchConst2 1000
#define turnLeft 750
#define turnRight 750
#define turnBack 1400
  int pLength = 0;
  int pIndex = 0;
  int mode = 0; 
  int wallDistance = 12; //distance from wall to robot
  int deviation = 5;
  int status = 0;
  
  char path[60] = {'0'};

  int buttonState = 0;
  int stage = 0;

void setup() {
  //Sensors Setup
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  //Motors Setup
  
  // motor A pin assignment
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorSpeedPinA, OUTPUT);
  pinMode(MotorBrakePinA, OUTPUT);

  // motor B pin assignment
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorSpeedPinB, OUTPUT);
  pinMode(MotorBrakePinB, OUTPUT);

  pinMode(buttonPin, INPUT);

}

void loop() 
{
    mazeSolve(); // First pass to solve the maze
}
void mazeSolve(void)
{
  unsigned int status = 0; // solving = 0; reach Maze End = 1
    while (!status)
    {
        mode = readSensors(); 
        Serial.print(LeftSensor);
        Serial.print(" - ");
        Serial.print(FrontSensor);
        Serial.print(" - ");
        Serial.println(RightSensor); 
        runExtraInch2();
        switch (mode)
        {   
          case GO_BACK:  
            brake('A',1);
            brake('B',1);
            goAndTurn (180);
            addPath('B');
            break;
            
         case GO_RIGHT: 
            goAndTurn (270); 
            runExtraInch();
            addPath('R');
            break;   
            
         case GO_LEFT: 
            goAndTurn (90); 
            runExtraInch();
            addPath('L');
            break;   
         
         case GO_STRAIGHT: 
            goStraight();
            break;  

         case FINISHED:
            brake('B', 1);
            brake('A', 1);
            status = 0;
            break;
        
         }
    }


}
void goAndTurn(int degrees)
{
  if (degrees == 90)
  {
    brake('B', 1);
    brake('B', 0);
    brake('A', 1);
    brake('A', 0);
    
    moveMotor('B', CW, 255);
    moveMotor('A', CW, 255);
    Serial.print(" left ");
    delay(turnLeft);
    brake('B', 1);
    brake('A', 1);
  }
  else if (degrees == 180)
  {
    brake('B', 1);
    brake('B', 0);
    brake('A', 1);
    brake('A', 0);
    
    moveMotor('B', CW, 255);
    moveMotor('A', CW, 255);
    Serial.print(" backwards ");
    
    delay(turnBack);
    brake('B', 1);
    brake('A', 1);
  }
  else if (degrees == 270)
  {
    brake('B', 1);
    brake('B', 0);
    brake('A', 1);
    brake('A', 0);
    
    moveMotor('B', CCW, 255);
    moveMotor('A', CCW, 255);
    Serial.print(" right ");
    delay(turnRight);
    brake('B', 1);
    brake('A', 1);
  }
}

void goStraight(void)
{
  brake('B', 1);
  brake('B', 0);
  brake('A', 1);
  brake('A', 0);
  moveMotor('B', CW, 255);
    moveMotor('A', CCW, 255);
    Serial.print(" straight ");
    delay(500);
   /**
  while (readSensors2() == 1)
  {
    moveMotor('B', CW, 255);
    moveMotor('A', CCW, 255);
    delay(1000);
  }
  */
  brake('B', 1);
  brake('A', 1);
}

void runExtraInch(void)
{
  /**
  brake('B', 1);
  brake('B', 0);
  brake('A', 1);
  brake('A', 0);
  
  moveMotor('B', CW, 255);
  moveMotor('A', CCW, 255);
  delay(runExtraInchConst);
  brake('B', 1);
  brake('A', 1);
  */
}
void runExtraInch2(void)
{
  /**
  brake('B', 1);
  brake('B', 0);
  brake('A', 1);
  brake('A', 0);
  
  moveMotor('B', CW, 255);
  moveMotor('A', CCW, 255);
  delay(runExtraInchConst2);
  brake('B', 1);
  brake('A', 1);
  */
}

//telling where to turn
void mazeTurn (char dir) 
{
  switch(dir)
  {
    case 'L': // Turn Left
       goAndTurn (90);      
       break;   
    
    case 'R': // Turn Right
       goAndTurn (270);     
       break;   
       
    case 'B': // Turn Back
       goAndTurn (180);     
       break;   
       
    case 'S': // Go Straight
       runExtraInch(); 
       break;
  }
}
/**
 * add Path and simplify path is inspired by an online guide and modified to our needs
 * 
 * */
//stores the path travelled and calls on simplify
void addPath(char direction)
{
  path[pLength] = direction; // Store the intersection in the path variable.
  pLength++;
  simplifyPath(); // Simplify the learned path.
}
//simplifies the path
void simplifyPath()
{
  // only simplify the path if the second-to-last turn was a 'B'
  if(pLength < 3 || path[pLength-2] != 'B')
    return;

  int totalAngle = 0;
  int i;
  for(i=1;i<=3;i++)
  {
    switch(path[pLength-i])
    {
      case 'R':
        totalAngle += 90;
        break;
      case 'L':
        totalAngle += 270;
        break;
      case 'B':
        totalAngle += 180;
        break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  totalAngle = totalAngle % 360;

  // Replace all of those turns with a single one.
  switch(totalAngle)
  {
    case 0:
      path[pLength - 3] = 'S';
      break;
    case 90:
      path[pLength - 3] = 'R';
      break;
    case 180:
      path[pLength - 3] = 'B';
      break;
    case 2255:
      path[pLength - 3] = 'L';
      break;
  }

  // The path has reduced by 2
  pLength -= 2;
  
} 

void mazeOptimization (void)
{
  for (int i = 0; i < pLength; ++i)
  {
    while(readSensors2() == 1)
    {
      goStraight;
    }
    mazeTurn(path[i]);
    runExtraInch();
  }
}
//check if path is straight
int readSensors2(void)
{
  SonarSensor(trigPin1, echoPin1);
  LeftSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  RightSensor = distance;
  SonarSensor(trigPin3, echoPin3);
  FrontSensor = distance;
  if (LeftSensor >= 0 && LeftSensor <= (wallDistance + deviation))
  {
    if (RightSensor >= 0 && RightSensor <= (wallDistance + deviation))
    {
      if (FrontSensor <= 0 && FrontSensor >= (wallDistance + deviation))
      {
        return 1;
      }
    }
  }
  return 0;
}
//check how car should turn
int readSensors (void)
{
  SonarSensor(trigPin1, echoPin1);
  LeftSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  RightSensor = distance;
  SonarSensor(trigPin3, echoPin3);
  FrontSensor = distance;
  /**
  if (!(LeftSensor >= 0 && LeftSensor <= (wallDistance + deviation)))
  {
    if (!(RightSensor >= 0 && RightSensor <= (wallDistance + deviation)))
    {
      if (!(FrontSensor >= 0 && FrontSensor <= (wallDistance + deviation)))
      {
        return FINISHED;
      }
    }
  }
  */
  if (LeftSensor >= 0 && LeftSensor <= (wallDistance + deviation))
  {
    if (RightSensor >= 0 && RightSensor <= (wallDistance + deviation))
    {
      if (FrontSensor >= 0 && FrontSensor <= (wallDistance + deviation))
      {
        return GO_BACK;
      }
      else
      {
        return GO_STRAIGHT;
      }
    }
    else if(FrontSensor>= 0 && FrontSensor <= (wallDistance + deviation))
    {
      return GO_RIGHT;
    }
    else 
    {
      return GO_STRAIGHT;
    }
  }
  else
  {
    return GO_LEFT;
  }
}
void SonarSensor(int trigPin,int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}

/*
  @param motor is char A or B refering to motor A or B.
  @param dir is motor direction, CW or CCW
  @speed is PWM value between 0 to 255
*/

void moveMotor(char motor, int dir, int speed)
{
  int motorPin;
  int motorSpeedPin;

  if (motor == 'A')
  {
    motorPin      = MotorPinA;
    motorSpeedPin = MotorSpeedPinA;
  }
  else
  {
    motorPin      = MotorPinB;
    motorSpeedPin = MotorSpeedPinB;
  }
  digitalWrite(motorPin, dir);// set direction for motor
  analogWrite(motorSpeedPin, speed);// set speed of motor
}//moveMotor end

/*
   brake, stops the motor, or releases the brake
   @param motor is character A or B
   @param brk if  1 brake, if 0, release brake
   example of usage:
   brake('A', 1);// applies brake to motor A
   brake('A', 0);// releases brake from motor A
*/
void brake(char motor, int brk)
{
  if (motor == 'A')
  {
    digitalWrite(MotorBrakePinA, brk);// brake
    //delay(1000);
  }
  else {
    digitalWrite(MotorBrakePinB, brk);// brake
    //delay(1000);

  }
}
