


int STATE = 1;
int Pulse = 1000;
int armingTime  = 0;
int motor1 = 9;
int motor2 = 6;
int motor3 = 3;


void setup()
{
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motor3,OUTPUT);

  for (armingTime = 0; armingTime < 500; armingTime++)
  {
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, HIGH);
    digitalWrite(motor3, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
    digitalWrite(motor3, LOW);
    delay(20-(Pulse/1000));
  }

}

void loop()
{


  for (Pulse = 900; Pulse <= 1900; Pulse++)
  {
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, HIGH);
    digitalWrite(motor3, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
    digitalWrite(motor3, LOW);
    delay(20-(Pulse/1000));

  }


  for (Pulse = 1900; Pulse >= 900; Pulse--)
  {
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, HIGH);
    digitalWrite(motor3, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
    digitalWrite(motor3, LOW);
    delay(20-(Pulse/1000));
  }
}
