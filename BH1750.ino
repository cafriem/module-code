#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Try initializing at address 0x23 first
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23)) {
    Serial.println(F("BH1750 initialized at address 0x23"));
  }
  // If that fails, try 0x5C
  else if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5C)) {
    Serial.println(F("BH1750 initialized at address 0x5C"));
  }
  else {
    Serial.println(F("BH1750 not found. Check wiring or power."));
  }
}

void loop() {
  float lux = lightMeter.readLightLevel();
  if (lux < 0) {
    Serial.println("Error reading BH1750!");
  } else {
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
  }
  delay(1000);
}