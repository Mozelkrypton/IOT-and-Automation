#include <Servo.h>

Servo gateServo;
int inches = 0;
int cm = 0;
int servoPosition = 0; // Track current servo angle

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  gateServo.attach(9);   // Servo signal pin
  gateServo.write(0);    // Start closed
}

void loop()
{
  // Measure distance
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  inches = cm / 2.54;

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");

  // --- Gate logic ---
  if (cm > 0 && cm <= 10)
  {
    if (servoPosition != 90)  // Only move if not already open
    {
      gateServo.write(90);    // Open gate
      servoPosition = 90;
      Serial.println("Gate OPEN");
    }
  }
  else if (cm > 10)
  {
    if (servoPosition != 0)   // Only move if not already closed
    {
      gateServo.write(0);     // Close gate
      servoPosition = 0;
      Serial.println("Gate CLOSED");
    }
  }

  delay(100); // Small delay for stable readings
}
