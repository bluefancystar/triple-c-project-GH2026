#include <DHT.h>
#include <Wire.h>
#include <SPI.h>

long duration;
double distance, distance_traveled, sum;
int count = 0;
double average = 0;
double left_dist = 0;
double right_dist = 0;
double dimensions[3];
double volume, temp, humid, light_level;

const int TH_TOGGLE = 27;
const int LIGHT_TOGGLE = 26;
const int VOLUME_TOGGLE = 25;
const int TRIG_PIN1 = 21;
const int ECHO_PIN1 = 15;
const int TRIG_PIN2 = 19;
const int ECHO_PIN2 = 4;
const int LIGHT_PIN = 13;
const int LED_PIN = 16;

//declares thermal/humidity sensor object
DHT th_sensor(23, DHT11); 

//function to calculate distance from object (averages 5 trials to reduce error)
double calculateDistance(const int TRIG_PIN, const int ECHO_PIN)
{
  for (int j = 0; j < 5; j++)
  {
    if (distance != 0)
    {
      sum += distance;
      count++;
    }
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    delayMicroseconds(10);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.println(distance);
    delay(50);
  }

  distance = 0;

  if (count != 0)
  {
    average = sum / count;
    sum = 0;
    count = 0;
    Serial.print("Average Distance: ");
    Serial.println(average);
  }
  return average;
}

//calculates volume
double calculateVolume()
{
  if (digitalRead(VOLUME_TOGGLE) == LOW)
  { 
    Serial.print("NV");
    return 0;
  }
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }
    digitalWrite(LED_PIN, HIGH);
    delay(1500);
    left_dist = calculateDistance(TRIG_PIN1, ECHO_PIN1);
    right_dist = 10 - calculateDistance(TRIG_PIN2, ECHO_PIN2);
    dimensions[i] = abs(right_dist - left_dist);
    digitalWrite(LED_PIN, LOW);
    delay(700);
  }
  volume = dimensions[0] * dimensions[1] * dimensions[2];
  Serial.print("Volume: ");
  return volume;
}

void setup()
{
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TH_TOGGLE, INPUT);
  pinMode(LIGHT_TOGGLE, INPUT);
  pinMode(VOLUME_TOGGLE, INPUT_PULLDOWN);

  Serial.begin(115200);
  th_sensor.begin();
}

void loop()
{

  if (digitalRead(TH_TOGGLE) == HIGH)
  {
    temp = th_sensor.readTemperature();
    humid = th_sensor.readHumidity();
    Serial.print("Temp in Celsius: ");
    Serial.println(temp);
    Serial.print("Humidity Percent: ");
    Serial.println(humid);
  }
  else
  {
    Serial.println("NT&H");
  }
  if (digitalRead(LIGHT_TOGGLE) == HIGH)
  {
    light_level = analogRead(LIGHT_PIN);
    Serial.print("Light: ");
    if (light_level < 2000)
    {
      Serial.println("LIGHT");
    }
    else
    {
      Serial.println("DARK");
    }
  }
  else
  {
    Serial.println("NL");
  }
  if (digitalRead(VOLUME_TOGGLE) == HIGH)
  {
    Serial.println(calculateVolume());
  }
  else
  {
    Serial.println("NV");
  }

  delay(2500);
}
