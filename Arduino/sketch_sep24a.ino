/* ------------------------------
 Lab 5-1  Output R2R, input to ADC
 The two least significant bits of PORTD (pins 0 and 1) of the Arduino
 are used by the serial port. 
 --------------------------------*/
void setup() {
  Serial.begin(115200);
  // DDRD is the direction register for Port D (Arduino digital pins 0-7).
  // The bits in this register control whether the pins in PORTD are
  // configured as inputs or outputs
  DDRD = B11111100;  // sets Arduino pins 2 to 7 as outputs
  PORTD = 0;         //
}

int i;   // Loop counter, R2R output
int Val[64]; // Array holds data from ADC
float Volts;  // 10-bit ADC data converted to voltage

void loop() {
  // Output values from 0 to 63 to R2R DAC
  // and read that value into the 10-bit ADC

  for ( i = 0; i < 64; i++) { 
    PORTD = (i << 2);  // Output value to R2R circuit on PORTD bits 2-7
    Val[i] = analogRead(0);   // Read ADC
  }

  for (i = 0; i < 64; i++) {
    Volts = (Val[i] / 1024.0) * 5.0;  // Convert 10-bit ADC value to volts
    Serial.println(Volts, 3 );        // 3 digit of fraction
  }

  while (1); // Stop
}

