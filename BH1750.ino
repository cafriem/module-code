// ---------------- normal run test ---------------------

// #include <BH1750.h>
// #include <Wire.h>

// BH1750 lightMeter;

// void setup() {
//   Serial.begin(9600);
//   Wire.begin();
//   lightMeter.begin();
// }

// void loop() {
//   float lux = lightMeter.readLightLevel();
//   Serial.print("Light: ");
//   Serial.print(lux);
//   Serial.println(" lx");
//   delay(1000);
// }


// ---------------- connection issue test ---------------------


// #include <Wire.h>

// void setup() {
//   Wire.begin();
//   Serial.begin(9600);
//   while (!Serial);
//   Serial.println("\nI2C Scanner");
// }

// void loop() {
//   byte error, address;
//   int nDevices = 0;
//   for(address = 1; address < 127; address++ ) {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
//     if (error == 0) {
//       Serial.print("I2C device found at address 0x");
//       if (address<16) Serial.print("0");
//       Serial.print(address,HEX);
//       Serial.println(" !");
//       nDevices++;
//     }
//   }
//   if (nDevices == 0)
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");
//   delay(2000);
// }

// ---------------- check addresses and run test ---------------------

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
