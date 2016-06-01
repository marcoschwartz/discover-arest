// Import required libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>

// WiFi parameters
const char* ssid     = "wifi-name";
const char* password = "wifi-pass";

// Clients
WiFiClient wifiClient;
PubSubClient client(wifiClient);

// Create aREST instance
aREST rest = aREST(client);

// Variables to be exposed to the API
bool ledState = false;

// Function
int ledControl(String command);
void callback(char* topic, byte* payload, unsigned int length);

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Set callback
  client.setCallback(callback);

  // Function to be exposed
  rest.function("toggle", ledToggle);

  // Give name and ID to device
  rest.set_id("40ty5c");
  rest.set_name("led");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Pin 5 as output
  pinMode(5, OUTPUT);

}

void loop() {

  // Connect to the cloud
  rest.handle(client);

}

// Custom function accessible by the API
int ledToggle(String command) {

  ledState = !ledState;

  digitalWrite(5, ledState);
  return 1;
}

// Handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {

  // Handle
  rest.handle_callback(client, topic, payload, length);

}
