//modes to see which way the car should go
#define GO_BACK 0
#define END_MAZE 1
#define GO_RIGHT 2
#define GO_LEFT 3
#define GO_STRAIGHT 4

//pins for sensors
#define trigPin1 A1
#define echoPin1 A2
#define trigPin2 A3
#define echoPin2 A4
#define trigPin3 A5
#define echoPin3 6

//pins for buttons
#define buttonPin 1

//Initializing variables for sensors
long duration, distance, RightSensor, FrontSensor, LeftSensor;

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
#define turnLeft 1000
#define turnRight 1000
#define turnBack 1000

void setup() {
  // put your setup code here, to run once:

  // motor A pin assignment
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorSpeedPinA, OUTPUT);
  pinMode(MotorBrakePinA, OUTPUT);

  // motor B pin assignment
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorSpeedPinB, OUTPUT);
  pinMode(MotorBrakePinB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  brake('B', 1);
  brake('B', 0);
  brake('A', 1);
  brake('A', 0);

  moveMotor('B', CW, 255); // Changing motor speed
  moveMotor('A', CCW, 255); // Changing motor speed
  delay(510); // Changing delay 
  brake('B', 1);
  brake('A', 1);
  delay(5000);
}

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
}

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
