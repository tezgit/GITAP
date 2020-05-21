// TeZ - TAP [Touch And Play] - Arduino sketch #1
// simple capacitive sensing detection 
 
// capacitive sensing includes
#include <CapacitiveSensor.h>

// capacitive sensing constant
CapacitiveSensor sensor = CapacitiveSensor(4,2);  // 1M resistor between pins 4 & 2, pin 2 is sensor pin

void setup() {
  Serial.begin(115200);
}

void loop() {
  long measurement =  sensor.capacitiveSensor(30);
  
  Serial.print("measurement: ");
  Serial.println(measurement); 
  delay(10);
}
