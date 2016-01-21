// Import required libraries
#include "ESP8266WiFi.h"
#include <aREST.h>

// Remote server
char* servername = "192.168.115.101";
int port = 3000;

// Create aREST instance
aREST rest = aREST(servername, port);

// WiFi parameters
const char* ssid = "Jarex_5A";
const char* password = "connect1337";

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);
WiFiClient restClient;

// Variable
bool motion = false;

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
  
  // Give name and ID to device
  rest.set_id("3");
  rest.set_name("esp8266_motion");
  
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

  // Set motion sensor pin
  pinMode(5, INPUT);
  
}

void loop() {
    
  // Reading temperature and humidity
  bool motionStatus = digitalRead(5);

  // Publish
  if (motionStatus != motion) {
    if (restClient.connect(servername, port)) {
      rest.publish(restClient, "motion", motionStatus);
    }
  }
  motion = motionStatus;
    
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
