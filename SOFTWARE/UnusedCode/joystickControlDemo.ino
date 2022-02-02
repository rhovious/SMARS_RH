#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7

int xAxis, yAxis;
unsigned int  x = 0;
unsigned int  y = 0;

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() 
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(38400);
}

void loop() 
{
  x = 510 / 4;
  y = 510 / 4;

  while (Serial.available() >= 2) 
  {
    x = Serial.read();
    delay(10);
    y = Serial.read();
  }
  delay(10);
  xAxis = x*4;
  yAxis = y*4;

  if (yAxis < 470) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  
  else if (yAxis > 550) 
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
  
  else 
  {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  if (xAxis < 470) {
   
    int xMapped = map(xAxis, 470, 0, 0, 255);
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    
    if (motorSpeedA < 0) 
    {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) 
    {
      motorSpeedB = 255;
    }
 }
     if (xAxis > 550) 
    {
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    if (motorSpeedA > 255) 
    {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) 
    {
      motorSpeedB = 0;
    }
  }
 
  if (motorSpeedA < 70) 
  {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) 
  {
    motorSpeedB = 0;
  }
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
}
