// Libraries
#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>
#include "DHT.h"

// DHT 11 sensor
#define DHTPIN 7
#define DHTTYPE DHT11 

// Remote server
char* servername = "192.168.115.101";
int port = 3000;

// DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Enter a MAC address for your controller below.
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40 };

// IP address in case DHCP fails
IPAddress ip(192,168,2,2);

// Ethernet server & client
EthernetServer server(80);
EthernetClient restClient;

// Create aREST instance
aREST rest = aREST(servername, port);

// Counter
int counter;

// Measurement interval
int measurement_interval = 60 * 1000; // 1 minute

// Variables to be exposed to the API
int temperature;
int humidity;

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Init variables and expose them to REST API
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("dapper_drake");

  // Start the Ethernet connection and the server
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  // Start counter 
  counter = millis();

}

void loop() {

  // Make measurements
  humidity = (int)dht.readHumidity();
  temperature = (int)dht.readTemperature();

  // Publish
  if ( (millis() - counter) > measurement_interval) {
    if (restClient.connect(servername, port)) {
      rest.publish(restClient, "temperature", temperature);
      rest.publish(restClient, "humidity", humidity);
    }
    counter = millis();
  }

  // Listen for incoming clients
  EthernetClient client = server.available();
  rest.handle(client);

}

