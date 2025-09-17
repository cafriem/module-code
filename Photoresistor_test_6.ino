const int sensorPin = A1;   // Photoresistor input
int lightLevel;
int high = 0, low = 1023;

void setup() {
  Serial.begin(9600); // start serial monitor
}

void loop() {
  // read light
  lightLevel = analogRead(sensorPin);

  // // auto-calibrate sensor range
  // if (lightLevel < low)  low = lightLevel;
  // if (lightLevel > high) high = lightLevel;

  // map light to 0–100%
  int percent = map(lightLevel, high, low, 100, 0);
  percent = constrain(percent, 0, 100);

  // print raw and percentage
  Serial.print("Raw: ");
  Serial.print(lightLevel);
  Serial.print(" | Light: ");
  Serial.print(percent);
  Serial.print(" %");

  // Serial.print(" | Low: ");
  // Serial.print(low);
  // Serial.print(" | High: ");
  // Serial.println(high);
  delay(200); // slow down printing
}

