#include <SoftwareSerial.h>

SoftwareSerial espSerial(10, 11);

void setup()
{
  Serial.begin(9600);
  espSerial.begin(9600);

  Serial.println("Arduino Ready");
}

void loop()
{
  if (espSerial.available())
  {
    String msg = espSerial.readStringUntil('\n');

    Serial.print("Received: ");
    Serial.println(msg);

    espSerial.println("Heyyy");
  }
}