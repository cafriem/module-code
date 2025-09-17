// YL-69 Soil Moisture Sensor Example
// Probe -> Analog pin
// VCC -> 5V, GND -> GND

int sensorPin = A0;   // YL-69 analog output connected to A0
int sensorValue = 0;  // variable to store sensor value

void setup() {
  Serial.begin(9600); // start serial monitor
}

void loop() {
  sensorValue = analogRead(sensorPin);  // read analog value (0–1023)
  
  Serial.print("Soil Moisture Value: ");
  Serial.println(sensorValue);

  // Optional: Simple dryness check
  if(sensorValue < 400) {
    Serial.println("Soil is Wet");
  } else if(sensorValue < 800) {
    Serial.println("Soil is Moist");
  } else {
    Serial.println("Soil is Dry");
  }

  delay(1000); // wait 1 second
}
