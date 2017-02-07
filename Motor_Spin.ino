//Prescott Rynewicz
// Sample Motor Spin code for Arduino
// Same algorithm can be transferred over to RPi, just need to transition code to Python
// and use RPi GPIO libraries.


// Constants

int STATE = 1;
int Pulse = 1000;         // Pulse is a milisecond measurement to update Pulse Width Modulated Freq.
int armingTime  = 0;      // Arming Time Variable used to arm motors open initial power.
int motor1 = 9;
int motor2 = 6;
int motor3 = 3;


void setup()
{
  // Define GPIO pin settings for Arduino
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motor3,OUTPUT);


  // When Speed Controllers recieve power, they expect to recieve a "Low Throttle Signal"
  // which corresponds to a 50Hz PWM signal.
  // From Line 41: (20 - Pulse/1000) = 19 :
  // Low Throttle: Turn on motors for one milisecond, and then turn off for 19 milisecond.
  // Full Throttle: Turn on motors for 2 milisecond, and then turn off for 18 milisecond.
  // All Measured within 50Hz (20ms) cycles.
  // https://www.rcgroups.com/forums/showthread.php?953916-RC-Throttle-signal-Noobie
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


// Varies motor inputs from off to full throttle.
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
