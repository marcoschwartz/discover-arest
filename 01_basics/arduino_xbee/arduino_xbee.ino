// Libraries
#include <SPI.h>
#include <aREST.h>
#include "DHT.h"

// Create aREST instance
aREST rest = aREST();

// DHT
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Variables
float temperature;
float humidity;

void setup(void)
{
  // Start Serial
  Serial.begin(9600);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("xbee");

  // Variables
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

  // Start DHT
  dht.begin();

}

void loop() {

  // Read data
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Handle REST calls
  rest.handle(Serial);

}
