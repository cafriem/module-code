// moisture sensor values
int moistSensorPin = A0;
int moistSensorValue = 0;

// photo resistor values
const int lightSensorPin = A1;   // Photoresistor input
int lightLevel;
int lightHigh = 0, lightLow = 1023;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // ------------- Moisture Sensor -------------

  // read moisture
  moistSensorValue = analogRead(moistSensorPin);

  // convert to percentage
  int moistPercent = map(moistSensorValue, 330, 1030, 100, 0);
  moistPercent = constrain (moistPercent, 0, 100);

  Serial.print("Soil Moisure Value: ");
  Serial.print(moistSensorValue);
  Serial.print("  |  ");
  Serial.print(moistPercent);
  Serial.println("%");


  // ------------- Light Sensor -------------


  // read light
  lightLevel = analogRead(lightSensorPin);

  // // auto-calibrate sensor range
  if (lightLevel < lightLow)  lightLow = lightLevel;
  if (lightLevel > lightHigh) lightHigh = lightLevel;

  // map light to 0–100%
  int lightPercent = map(lightLevel, lightHigh, lightLow, 100, 0);
  lightPercent = constrain(lightPercent, 0, 100);

  // print raw and percentage
  Serial.print("Light Value       : ");
  Serial.print(lightLevel);
  Serial.print(" | Light: ");
  Serial.print(lightPercent);
  Serial.println(" %");

  // Serial.print(" | lightLow: ");
  // Serial.print(lightLow);
  // Serial.print(" | lightHigh: ");
  // Serial.println(lightHigh);
  delay(500); // slow down printing
}
