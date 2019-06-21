// MovingAverage.ino
// Reads data on analog input sensorPin and computes a moving
// average of FILTER_SIZE data points and prints to serial out.
// Pulling digital input pin 2 low disables the moving average and outputs
// the raw data value.
//
// Signal Conditioning:
// DC motor connected to variable voltage source on one end and the other
// end connected to a 1 ohm sensing resistor connected to ground.
// The voltage across the sensing resistor is connected to a noninverting amp
// of gain +11.
// The output of the amp is connected to a second order active filter of gain +1.
// The output of the filter is connected to the analog input sensorPin.

#define FILTER_SIZE 11  // Number of data points in the moving average

int sensorPin = A0;            // select the input pin for the current sensing resistor
int disableMovingAverage = 2;  // Digital input on pin 2
int movingArray[FILTER_SIZE + 1]; // Array holding  running data values
int iNewest = FILTER_SIZE ;    // Index into movingArray for newest data value
int iOldest = 0;               // Index into movingArray for oldest data value
int sampleValue;               // Value from ADC
float movingAverageValue;      // Result of moving average computation
float  current;                // For Lab 9 we are averaging current values
float ampGain = 11.0;          // Gain of the signal conditioning amplifer
int sum;                       // The moving accumulated sum to be divided
             //     by FILTER_SIZE to get moving average
long Vcc_mV;                   // Calibrated Vcc in mv: nominal value is 5000 for +5 V
float Vcc;                     // Calibrated Vcc in volts


long readVcc() {  // Calibrates the +5 V used as ADC reference
// http://code.google.com/p/tinkerit/wiki/SecretVoltmeter
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  // Vcc = (1100 * 1024) / ADC
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

// update and wrap around the indices in the moving data array
void updateMovingArrayIndices() {
  iNewest++;
  if (iNewest > FILTER_SIZE) iNewest = 0;
  iOldest++;
  if (iOldest > FILTER_SIZE) iOldest = 0;
}

void setup() {
  pinMode(disableMovingAverage, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Moving Average of data on Analog Channel 0");
  Serial.println("Grounding digital pin 2 disables moving average - prints raw value");
  Vcc_mV = readVcc();    // Vcc in mV
  Vcc = Vcc_mV / 1000.0; // Vcc in volts
  Serial.print("Calibrated Vcc = "); Serial.println(Vcc);
  delay(2000);
}

void loop() {
  sampleValue = analogRead(sensorPin);

  // If digital pin 2 is low, output raw sampleValue
  if (digitalRead(disableMovingAverage) == LOW) {
    current = 1000.0 * (Vcc / 1024.0) * sampleValue / ampGain; // in mA
    Serial.print("sampleValue = ");
    Serial.print(sampleValue);
    Serial.print(" sampleValue in Volts = ");
    Serial.print((sampleValue / 1024.0)*Vcc);
    Serial.print(" current, mA = ");
    Serial.println(current);
  }
  // If digital pin 2 is open (high), print movingAverageValue
  else {
    updateMovingArrayIndices();
    movingArray[iNewest] = sampleValue;
    sum = sum + movingArray[iNewest] - movingArray[iOldest];
    movingAverageValue = (float) sum / (float) FILTER_SIZE;
    current = 1000.0 * (Vcc / 1024.0) * movingAverageValue / ampGain;  // in mA
    Serial.print(" movingAverageValue = ");
    Serial.print(movingAverageValue);
    Serial.print(" movingAverageValue in Volts = ");
    Serial.print((movingAverageValue / 1024.0)*Vcc);
    Serial.print(" current, mA = ");
    Serial.println(current);
  }

  delay(100);
}

