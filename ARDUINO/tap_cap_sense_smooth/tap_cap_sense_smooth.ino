// TeZ - TAP [Touch And Play] - Arduino sketch #2
// simple capacitive sensing detection with smoothing
 
// capacitive sensing includes
#include <CapacitiveSensor.h>

const long numReadings = 100;

long readings[numReadings];      // the readings from the analog input
long readIndex = 0;              // the index of the current reading
long total = 0;                  // the running total
long average = 0;                // the average

// capacitive sensing constant
CapacitiveSensor sensor = CapacitiveSensor(4,2);  // 1M resistor between pins 4 & 2, pin 2 is sensor pin

///////////////////////////////////
void setup() {
  Serial.begin(115200);

  // init reading buffer
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
}

///////////////////////////////////
void loop() {
  
  long measurement =  sensor.capacitiveSensor(30); // read from capsense circuit
  
  total = total - readings[readIndex];
  readings[readIndex] = measurement;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  Serial.println(average);
  delay(1);        // delay in between reads for stability

}
