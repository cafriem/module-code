==============================
 CAPACITIVE SOIL MOISTURE SENSOR V1.2 — NOTES
==============================

------------------------------------------------------------
[1] OVERVIEW
------------------------------------------------------------
- Measures soil moisture by detecting changes in capacitance.
- Uses a 555 timer (NE555) circuit to convert capacitance changes 
  into a measurable analog voltage.
- Non-corrosive: no exposed metal electrodes.
- Compatible with 3.3V and 5V systems (Arduino, ESP32, etc.).
- Output is an analog voltage that varies with moisture level.

------------------------------------------------------------
[2] WORKING PRINCIPLE
------------------------------------------------------------
- The sensor acts as a capacitor. The PCB traces form plates, 
  and the soil acts as the dielectric.
- Wet soil → higher dielectric constant → higher capacitance.
- A 555 timer generates an oscillating frequency based on capacitance.
- This frequency is converted into a steady analog voltage output.
- Microcontrollers read this voltage through an analog input pin.

------------------------------------------------------------
[3] TECHNICAL SPECIFICATIONS
------------------------------------------------------------
Operating Voltage   : 3.3V – 5.5V DC
Current Draw        : ~5 mA
Output Type         : Analog Voltage
Output Impedance    : ~10 kΩ
Measurement Type    : Capacitive (non-corrosive)
Response Time       : < 1 second
Operating Temp      : 0°C – 60°C
Recommended Depth   : 4–6 cm (keep sensing area covered)

------------------------------------------------------------
[4] PINOUT
------------------------------------------------------------
Pin | Label | Description
----|--------|--------------------------------
1   | VCC   | Power supply (3.3V–5.5V)
2   | GND   | Ground
3   | AOUT  | Analog voltage output (to ADC pin)

------------------------------------------------------------
[5] INTERNAL CIRCUIT (SIMPLIFIED)
------------------------------------------------------------
Main components:
- NE555 timer IC → generates oscillation based on capacitance.
- RC network → timing components; "C" is the soil capacitor.
- Low-pass filter → converts oscillation to smooth analog voltage.
- 100nF capacitor → between VCC & GND for power noise filtering.

Function flow:
1. NE555 produces square wave pulses.
2. Capacitance changes with soil moisture.
3. Frequency of pulses changes accordingly.
4. Filter smooths signal → voltage level changes with moisture.

------------------------------------------------------------
[6] OUTPUT BEHAVIOR (APPROXIMATE)
------------------------------------------------------------
Soil Condition | Capacitance | 555 Freq | Output Voltage
---------------|--------------|----------|----------------
Very Dry       | Low          | High     | ~0.5 V
Moist          | Medium       | Medium   | ~1.5 V
Wet            | High         | Low      | ~3.0 V

(Note: exact voltages vary by sensor and soil type)

------------------------------------------------------------
[7] ELECTRICAL NOTES
------------------------------------------------------------
- Wait ~1 second after powering before reading (stabilization).
- Add 100nF capacitor between VCC and GND for noise filtering.
- Keep analog wire short (<30 cm) to avoid noise.
- Use shielded cable or analog buffer if using long wires.

------------------------------------------------------------
[8] PHYSICAL DESIGN
------------------------------------------------------------
- Material: FR-4 PCB.
- Protective epoxy coating on probe.
- Long flat shape for good sensing area.
- Insert ~3/4 of probe into soil (do not bury whole board).

------------------------------------------------------------
[9] OUTPUT IMPEDANCE
------------------------------------------------------------
- Output Impedance: ~10 kΩ
- Meaning: internal resistance of the output signal.
- Effect: suitable for analog inputs but not for driving loads.
- If using long wires (>1m), add an op-amp buffer to prevent signal loss.

------------------------------------------------------------
[10] POWER & HEAT SAFETY
------------------------------------------------------------
Power use: 5V * 5mA = 0.025W (no heat concern)
Safe for continuous use.
Avoid:
- Supplying >5.5V
- Shorting pins
- Exposing uncoated parts to high humidity

------------------------------------------------------------
[11] COMMON PROBLEMS & FIXES
------------------------------------------------------------
Issue                         | Cause                          | Fix
------------------------------|--------------------------------|----------------------------
Output constant / stuck       | No analog signal / wiring issue| Check AOUT, power, GND
Noisy / unstable readings     | Power noise or long cable      | Add 100nF capacitor
Inverted readings             | Different polarity expectation | Adjust mapping in code
Wrong calibration             | Different soil types           | Calibrate manually (dry/wet)

------------------------------------------------------------
[12] CALIBRATION & CODE EXAMPLE
------------------------------------------------------------
In Arduino/ESP32:

int raw = analogRead(A0);
float moisture = map(raw, dryValue, wetValue, 0, 100);

Where:
- dryValue = reading in dry soil
- wetValue = reading in fully wet soil
- Output is % moisture

------------------------------------------------------------
[13] SUMMARY
------------------------------------------------------------
Soil moisture changes capacitance →
Changes 555 timer frequency →
Circuit converts frequency to voltage →
Microcontroller reads voltage as analog value.

------------------------------------------------------------
[14] QUICK FACTS
------------------------------------------------------------
- Output range: ~0.5–3.0V (depends on moisture)
- Frequency range (internal)
