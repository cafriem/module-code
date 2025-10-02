int sensorValue = 0;

// Change these after calibration:
int airValue = 473;   // Value when sensor is in air (dry)
int waterValue = 203; // Value when sensor is in water (wet)

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(A0);

  // Map raw values to percentage
  int moisturePercent = map(sensorValue, airValue, waterValue, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Raw: ");
  Serial.print(sensorValue);
  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.println(" %");

  delay(500);
}