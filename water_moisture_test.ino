int sensorPin = A0;

int sensorVal = 0;

// to scale the high and low of moisture
int moistLow = 330;
// 5V
// int moistHigh = 1023;
// 3.3V
int moistHigh = 675;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorVal = analogRead(sensorPin);

  // calibrate the highest and lowest readings
  if (sensorVal < moistLow) {
    moistLow = sensorVal;
  }
  if (sensorVal > moistHigh) {
    moistHigh = sensorVal;
  }

  int percent = map(sensorVal, moistLow, moistHigh, 100, 0);
  percent = constrain (percent, 0, 100);

  Serial.print("Soil Moisure Value: ");
  Serial.print(sensorVal);
  Serial.print("  |  ");
  Serial.print(percent);
  Serial.println("%");
  delay(500);
}