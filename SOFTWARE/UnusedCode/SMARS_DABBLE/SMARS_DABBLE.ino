//SMARS Demo 3 with ultrasonic sensor
//This sketch makes the robot avoid obstacles.
//you'll need a motor driver https://goo.gl/v8ADzU   and an ultrasonic sensor https://goo.gl/upDRNi

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

int lmotorpin1 = 5;
int lmotorpin2 = 6;
int rmotorpin1 = 6;
int rmotorpin2 = 10;
//int distancecm=0;
//const int trigPin = 3;
//const int echoPin = 11;
// defines variables
long duration;
int driveDelay = 10000;
//int distance;

void testDrive(int durationInput) {
  int duration = durationInput;
  Serial.println("Driving");
  digitalWrite(lmotorpin1, LOW);
  digitalWrite(lmotorpin2, HIGH);
  digitalWrite(rmotorpin1, LOW);
  digitalWrite(rmotorpin2, HIGH);
  delay(driveDelay);
  digitalWrite(lmotorpin1, LOW);
  digitalWrite(lmotorpin2, HIGH);
  digitalWrite(rmotorpin1, HIGH);
  digitalWrite(rmotorpin2, LOW);
  Serial.println("Driving Done");
  delay(driveDelay);

}

void handleSticks() {

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
}


void handleButtons() {
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("UP");
    Serial.println("Driving");
    digitalWrite(lmotorpin1, LOW);
    digitalWrite(lmotorpin2, HIGH);
    digitalWrite(rmotorpin1, LOW);
    digitalWrite(rmotorpin2, HIGH);
  }

  if (GamePad.isDownPressed())
  {
    Serial.print("DOWN");
    digitalWrite(lmotorpin1, LOW);
    digitalWrite(lmotorpin2, HIGH);
    digitalWrite(rmotorpin1, HIGH);
    digitalWrite(rmotorpin2, LOW);
    Serial.println("Driving Done");
  }

  if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
  }

  if (GamePad.isRightPressed())
  {
    Serial.print("Right");
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  Serial.print('\t');

}





void setup() {
  Serial.begin(115200);
  Dabble.begin(9600);      //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.

  pinMode(lmotorpin1, OUTPUT);
  pinMode(lmotorpin2, OUTPUT);
  pinMode(rmotorpin1, OUTPUT);
  pinMode(rmotorpin2, OUTPUT);
  //pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  //pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.println("Setup Done");
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  //testDrive(0);
  handleButtons();
  handleSticks();

  //distancecm=mdistance();
  /*
    if(distance<5){
    digitalWrite(lmotorpin1,LOW);
    digitalWrite(lmotorpin2,HIGH);
    digitalWrite(rmotorpin1,LOW);
    digitalWrite(rmotorpin2,HIGH);
    delay(1000);
     digitalWrite(lmotorpin1,LOW);
    digitalWrite(lmotorpin2,HIGH);
    digitalWrite(rmotorpin1,HIGH);
    digitalWrite(rmotorpin2,LOW);
    delay(1000);
    }
    else{
    digitalWrite(rmotorpin1,HIGH);
    digitalWrite(rmotorpin2,LOW);
    digitalWrite(lmotorpin1,HIGH);
    digitalWrite(lmotorpin2,LOW);
    }
  */



  //int mdistance()


  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  //duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  //distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");



}
