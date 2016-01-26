// Import required libraries
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include <aREST.h>
#include <avr/wdt.h>
#include "DHT.h"

// DHT11 sensor pins
#define DHTPIN 4
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// These are the pins for the CC3000 chip if you are using a breakout board
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// Create CC3000 instance
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2);
// Create aREST instance
aREST rest = aREST();

// Your WiFi SSID and password
#define WLAN_SSID       "wifi-name"
#define WLAN_PASS       "wifi-password"
#define WLAN_SECURITY   WLAN_SEC_WPA2

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Server instance
Adafruit_CC3000_Server restServer(LISTEN_PORT);

// Variables
int temperature;
int humidity;

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Init DHT
  dht.begin();

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("cc3000");

  // Expose variables
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

  // Set up CC3000 and get connected to the wireless network.
  Serial.print(F("CC3000 init ... "));
  if (!cc3000.begin())
  {
    while(1);
  }

  Serial.println(F(" done"));

  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    while(1);
  }
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }
  Serial.println();

  // Print CC3000 IP address. Enable if mDNS doesn't work
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  // Start server
  restServer.begin();
  Serial.println(F("Listening for connections..."));

  // Enable watchdog
  wdt_enable(WDTO_4S);
}

void loop() {

  // Reading temperature and humidity
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Handle REST calls
  Adafruit_CC3000_ClientRef client = restServer.available();
  rest.handle(client);
  wdt_reset();

  // Check connection, reset if connection is lost
  if(!cc3000.checkConnected()){while(1){}}
  wdt_reset();

}

// Print connection details of the CC3000 chip
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
