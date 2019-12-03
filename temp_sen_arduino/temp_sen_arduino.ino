#include "DHT.h"

#define DHTTYPE DHT11
#define SENSOR_PIN 5
#define SENSOR_PIN2 6

DHT dht(SENSOR_PIN, DHTTYPE);
DHT dht2(SENSOR_PIN2, DHTTYPE);

void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float t = dht.readTemperature();
  float t2 = dht2.readTemperature();
  Serial.print("Temperature1 = ");
  Serial.println(t);
  Serial.print("Temperature2 = ");
  Serial.println(t2);

  if (t < 30 && t2 < 30) {
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  } else if (t > 30 && t2 < 30) {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  } else if (t < 30 && t2 > 30) {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  } else if (t > 30 && t2 > 30) {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  }
}

