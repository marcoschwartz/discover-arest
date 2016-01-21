// Libraries
#include <SPI.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("serial");

}

void loop() {

  // Handle REST calls
  rest.handle(Serial);

}
