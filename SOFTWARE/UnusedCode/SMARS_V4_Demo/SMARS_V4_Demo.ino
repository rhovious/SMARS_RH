//SMARS Demo 3 with ultrasonic sensor
//This sketch makes the robot avoid obstacles.
//you'll need a motor driver https://goo.gl/v8ADzU   and an ultrasonic sensor https://goo.gl/upDRNi



#define lmotorpin1 5  // Motor A pins
#define lmotorpin2 6
#define rmotorpin1 10 // Motor B pins
#define rmotorpin2 11



//int distancecm=0;
//const int trigPin = 3;
//const int echoPin = 11;
// defines variables
long duration;
int driveDelay = 10000;
//int distance;

void forward() {          //function of forward 
  Serial.println("FORWARD");
  analogWrite(lmotorpin1, 255);
  analogWrite(lmotorpin2, 0);
  analogWrite(rmotorpin1, 255);
  analogWrite(rmotorpin2, 0);
}

void backward() {         //function of backward
  Serial.println("BACKWARD");
  analogWrite(lmotorpin1, 0);
  analogWrite(lmotorpin2, 210);
  analogWrite(rmotorpin1, 0);
  analogWrite(rmotorpin2, 210);
}

void Stop() {              //function of stop
  Serial.println("STOP");
  digitalWrite(lmotorpin1, LOW);
  digitalWrite(lmotorpin2, LOW);
  digitalWrite(rmotorpin1, LOW);
  digitalWrite(rmotorpin2, LOW);
}

void testDrive(int durationInput) {
  int duration = durationInput;
  Serial.println("Driving");
  forward();
  delay(driveDelay);
  backward();
  delay(driveDelay);
  Stop();
 
  Serial.println("Driving Done");
  delay(driveDelay);

}





void setup() {
  Serial.begin(115200);

  pinMode(lmotorpin1, OUTPUT);
  pinMode(lmotorpin2, OUTPUT);
  pinMode(rmotorpin1, OUTPUT);
  pinMode(rmotorpin2, OUTPUT);
  //pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  //pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.println("Setup Done");
}

void loop() {

  testDrive (0);

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

}

int mdistance()
{





  //digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  //digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  //duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  //distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");



}
