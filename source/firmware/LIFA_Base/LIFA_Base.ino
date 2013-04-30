

/*********************************************************************************
 **
 **  LVFA_Firmware - Provides Basic Arduino Sketch For Interfacing With LabVIEW.
 **
 **  Written By:    Sam Kristoff - National Instruments
 **  Written On:    November 2010
 **  Last Updated:  Dec 2011 - Kevin Fort - National Instruments
 **
 **  This File May Be Modified And Re-Distributed Freely. Original File Content
 **  Written By Sam Kristoff And Available At www.ni.com/arduino.
 **
 *********************************************************************************/


/*********************************************************************************
 **
 ** Includes.
 **
 ********************************************************************************/ 
// Standard includes.  These should always be included.
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "LabVIEWInterface.h" 
#include "spo2.h"

SoftwareSerial spo2(3,2);

uint8_t spo2_data[5]; 
uint8_t addr;
uint8_t state, next_state;
/*********************************************************************************
 **  setup()
 **
 **  Initialize the Arduino and setup serial communication.
 **
 **  Input:  None
 **  Output: None
 *********************************************************************************/
void setup()
{  
  // Initialize Serial Port With The Default Baud Rate
  syncLV();
  spo2.begin(9600);
  spo2.listen();
  addr = 0;
  // Place your custom setup code here
  
}


/*********************************************************************************
 **  loop()
 **
 **  The main loop.  This loop runs continuously on the Arduino.  It 
 **  receives and processes serial commands from LabVIEW.
 **
 **  Input:  None
 **  Output: None
 *********************************************************************************/
void loop()
{   
  // Check for commands from LabVIEW and process them.   
  int byte;
  checkForCommand();
  /* typedef a struct container for data values */
  /* declare the struct in LabviewInterface.ino */
  /* make a new Labview command that responds with the SPO2 data */
  if(spo2.available()) {
      while((byte = spo2.read()) >= 0) {
          byte = (uint8_t)byte;
          if(byte >= WAVE_MARKER) {
          }
          switch(byte) {
              case PULSE_MARKER:
                  /* next byte contains pulse data */
              case SPO2_MARKER:
                  /* next byte contains spo2 data */
              case WAVE_MARKER:
                  /* next byte contains wave data */
              case INFO_MARKER:
                  /* next byte contains info data */
              case QUALITY_PERFUSION_MARKER:
                  /* next byte contains q/p data */
                  next_state = UPDATE_DATA;
                  addr = SPO2_INDEX(byte); // addr = byte - offset
                  break;
              default:
                  next_state = IDLE;
          }
          switch(state) {
              case UPDATE_DATA:
                  *(spo2_data + addr) = byte;
                  state = IDLE;
                  break;
              default:
                  state = next_state;                  
          }
      }
  }
  // Place your custom loop code here (this may slow down communication with LabVIEW)
  
  
  if(acqMode==1)
  {
    sampleContinously();
  }

}














