#include <SPI.h>
#define GAIN_MAX 16 /* 0000 1111, 16 in decimal. 16 == max gain available */
#define GAIN_MIN 1
#define ADMAX 1023
#define GAIN_MASK 0x0F

/*
  The Arduino SPI pins are:
  Master In Slave Out (MISO) 12
  Master Out Slave In (MOSI) 11
  Serial Clock (SCK) 13
  Chip Select pin (CS) 10 (active low)

  The LMP8100 amplifier reads data on the rising edge of the
  clock. The clock has to be HIGH when the CS pin is pulled low. This
  means SPI mode 02 with CPOL 1 and CPHA 0. The SPI modes are documented in

  http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus

  The SDO pin on the amplifier is connected to the MISO pin of Arduino
  in order to read the old gain value back from the device. The old
  gain value was used in the most recent data value so it shall be
  recorded.

  The gain is increased (if possible) when the signal value has
  drifted away from the nominal value (to be decided, eg. 800). Also
  take into consideration that the gain value should remain the same
  when a sudden change occurs in the EDR value during measurement,
  ie. the test subject is nervous. The correct way to increase gain
  might be to let the host computer request a higher gain if deemed
  necessary.

  -HL

*/

// the setup routine runs once when you press reset:
void setup() {
    // initialize serial communication at 9600 bits per second:
    Serial.begin(115200);
    SPI.begin(); // initialize pin modes and possibly other stuff
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE2); // clock idle high & propagate data on rising edge
    // initialize gain to 1
}

uint8_t gain = 1;
uint8_t oldGain = 1;
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0: EDR-pinni?
  uint16_t sensorValue = analogRead(A0);
  if (sensorValue == ADMAX && gain > GAIN_MIN) {
    oldGain = SPI.transfer(--gain);
  } else if (abs(2*sensorValue - ADMAX) > 300 && gain < GAIN_MAX) {
    oldGain = SPI.transfer(++gain);
  }
  Serial.println(sensorValue);
  Serial.println(oldGain);
}
