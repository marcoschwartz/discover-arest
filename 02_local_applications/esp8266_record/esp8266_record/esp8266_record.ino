// Import required libraries
#include "ESP8266WiFi.h"
#include <aREST.h>
#include "DHT.h"

// DHT11 sensor pins
#define DHTPIN 5
#define DHTTYPE DHT11

// Remote server
char* servername = "192.168.115.101";
int port = 3000;

// Create aREST instance
aREST rest = aREST(servername, port);

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// WiFi parameters
const char* ssid = "Jarex_5A";
const char* password = "connect1337";

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);
WiFiClient restClient;

// Counter
int counter;

// Measurement interval
int measurement_interval = 60 * 1000; // 1 minute

// Variables
float temperature;
float humidity;

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
  
  // Init DHT 
  dht.begin();
  
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.println(WiFi.localIP());

  // Start counter 
  counter = millis();
  
}

void loop() {
    
  // Reading temperature and humidity
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Publish
  if ( (millis() - counter) > measurement_interval) {
    if (restClient.connect(servername, port)) {
      rest.publish(restClient, "temperature", temperature);
      rest.publish(restClient, "humidity", humidity);
    }
    counter = millis();
  }
    
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
 
}
