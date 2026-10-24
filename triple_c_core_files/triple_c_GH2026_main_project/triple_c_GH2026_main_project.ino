#include <ESP32Servo.h>

long duration;
double distance_b = 0;
double distance_f = 0;
double distance_traveled;
double sum;
int count = 0;
double average_b;
double average_f;

const int SERVO_PIN = 22;
const int TRIG_PIN1 = 21;
const int ECHO_PIN1 = 15;
const int TRIG_PIN2 = 19;
const int ECHO_PIN2 = 4;
const int BUTTON_PIN = 18;

Servo servo;

void calculateDistance(TRIG_PIN, ECHO_PIN)
{
  for (int j = 0; j < 5; j++)
  {
    if (distance_b != 0)
    {
      sum += distance_b;
      count++;
    }
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    delayMicroseconds(10);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance_b = duration * 0.034 / 2;

    Serial.print("Distance_b: ");
    Serial.println(distance_b);
    delay(50);
  }

  distance_b = 0;

  if (count != 0)
  {
    average_b = sum / count;
    sum = 0;
    count = 0;
    Serial.print("Average Distance_b: ");
    Serial.println(average_b);
  }
    
  servo.write(0);
  for (int i = 0; i <= 180; i += 45)
  {
    servo.write(i);
    delay(5);
  }
  delay(750);

  for (int j = 0; j < 5; j++)
  {
    if (distance_f != 0)
    {
      sum += distance_f;
      count++;
    }
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    delayMicroseconds(10);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance_f = duration * 0.034 / 2;

    Serial.print("Distance_f: ");
    Serial.println(distance_f);
    delay(50);
  }

  distance_f = 0;

  if (count != 0)
  {
    average_f = sum / count;
    sum = 0;
    count = 0;
    Serial.print("Average Distance_f: ");
    Serial.println(average_f);
  }

  distance_traveled = distance_b - distance_f;
  Serial.print("Distance travled: ");
  Serial.println(distance_traveled);
    
  servo.write(0);
}

void calculateSize()
{
  calculateDistance(TRIG_PIN1, ECHO_PIN1);
  calculateDistance(TRIG_PIN2, ECHO_PIN2);
}

void setup()
{
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 500, 2400);

  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  Serial.begin(115200);
  servo.write(0);
}

void loop()
{
  
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    calculateDistance(TRIG_PIN1, ECHO_PIN1);
  }
}
