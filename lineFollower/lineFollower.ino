#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myRightMotor = AFMS.getMotor(3);
// You can also make another motor on port M2
Adafruit_DCMotor *myLeftMotor = AFMS.getMotor(4);

const int rightSensor = 2;
const int leftSensor = 3;

double val_r = 0;
double val_l = 0;

double c = 26.0;

double leftspeed;
double rightspeed;

String incoming;

float start = millis();

void setup() 
{
  Serial.begin(9600);          
  AFMS.begin();  // create with the default frequency 1.6KHz 

  myRightMotor->run(FORWARD);
  myLeftMotor->run(FORWARD);
  Serial.print(start);
}


void loop() 
{
  read_serial();
  //SENSORS SENSORS SENSORS
  val_r = analogRead(rightSensor);
  val_l = analogRead(leftSensor);
  //Serial.print("Right Sensor:"); Serial.print(val_r);
  //Serial.print("Left Sensor:"); Serial.println(val_l);

  leftspeed = (val_l/val_r)*c; 
  rightspeed = (val_r/val_l)*c;

  if (leftspeed < rightspeed)
  {
    leftspeed = leftspeed / 2.0;
  }
  else if (leftspeed > rightspeed)
  {
    rightspeed = rightspeed / 2.0;
  }
  else if (abs(leftspeed - rightspeed) < 10)
  {
    // keep speeds the same
  }

  if (millis() - start <= 15000.0)
  {
    Serial.print(millis());            Serial.print(",");
    Serial.print(val_l);               Serial.print(",");
    Serial.print(val_r);               Serial.print(",");
    Serial.print((int) leftspeed);     Serial.print(",");
    Serial.println((int) rightspeed);
  }
  else
  {
    Serial.print(-1);               Serial.print(",");
    Serial.print(-1);               Serial.print(",");
    Serial.print(-1);               Serial.print(",");
    Serial.print(-1);               Serial.print(",");
    Serial.println(-1);
  }
  myLeftMotor->setSpeed((int) leftspeed);
  myRightMotor->setSpeed((int) rightspeed);
}

void read_serial() 
{
  if (Serial.available() > 0) 
  {
    // read the incoming:
    incoming = Serial.readString();
    if (incoming == "fast")
    {
      c = 25;
      Serial.print("Your speed constant is now equal to: ");
      Serial.println(c);
    }
    else if (incoming == "slow")
    {
      c = 20;
      Serial.print("Your speed constant is now equal to: ");
      Serial.println(c);
    }
    else
    {
      Serial.println("That command is invalid. Please enter 'fast' or 'slow'");
    }
  }  
}
