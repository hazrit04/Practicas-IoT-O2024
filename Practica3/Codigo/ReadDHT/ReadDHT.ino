
#include "DHT.h"
#define DHTPIN 15
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
Serial.begin(9600);
Serial.println(F("DHTxx test!"));
dht.begin();
}


void loop()
{
    delay(2000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if(isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    
    Serial.println("Temperatura en el sensor");
    Serial.println(t);
    Serial.println("Humedad en el sensor");
    Serial.println(h);

}
