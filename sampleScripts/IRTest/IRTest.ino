int analogPin = 3;
int analogPin2 = 2;

int val = 0;
int val2 = 0;          
void setup()
{
  Serial.begin(9600);              //  setup serial
}

void loop()
{
  val = analogRead(analogPin);
  val2 = analogRead(analogPin2);    
  Serial.print("Right Sensor:"); Serial.print(val);
  Serial.print("Left Sensor:"); Serial.println(val2);               
}
