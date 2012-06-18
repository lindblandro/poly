
#define GAIN_MASK 0x0F /* 0000 1111, 16 in decimal. 16 == max gain available */
/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the 
serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}

float EDRvalue = 0;
uint8_t gain = 1;

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0: EDR-pinni?
  uint16_t sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage); // does not print expected results.
  if (voltage > EDRvalue){
      gain = (gain - 1) & GAIN_MASK;
  }
  if (voltage < EDRvalue){
      gain = (gain + 1) & GAIN_MASK;
  }
  EDRvalue = voltage;
}
//return gain;  kts. SPI-jutut
