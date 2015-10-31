/**********************************************************************************************************/
/* OneWire old DS1820 and new DS18S20, DS18B20, DS1822 temperature example
 * Displays temperature in Celcius, Fahrenheit and Kelvin to serial monitor
 * 
 * Origin Author:        http://www.pjrc.com/teensy/td_libs_OneWire.html
 *                       The DallasTemperature library can do all this work for you!
 *                       http://milesburton.com/Dallas_Temperature_Control_Library
 *
 * Modified by:          Olaf Meier
 *
 * Hardware connection:  Add a 4.7k to 10k between Data and Vdd as PullUp
 *                        ---     DS1820 View from front, flat side with print
 *                       |   |    
 *                        ---     1 = GND
 *                       | | |    2 = Data
 *                       1 2 3    3 = Vdd 5V
 * 
 * ToDo:
 * 
 */
/**********************************************************************************************************/
/*
 * Example of output via Serial Monitor:
 *
 * ROM = 10 B3 C1 4B 2 8 0 7
 * Chip = DS18S20
 * Data = 1 2E 0 4B 46 FF FF B 10 6E  CRC=6E
 * Temperature = 23.06 Celsius / 73.51 Fahrenheit / 296.21 Kelvin
 * No more addresses.
 *
 *
 */
/**********************************************************************************************************/
/**********************************************************************************************************/
/***  Declaration of global constants and initialization of variables. Add includes.  ***/
/**********************************************************************************************************/
/***  Software release and date  ***/
const char* author                =  "Olaf Meier";
const char* revision              =  "R.1.0";
const char* date                  =  "2012/10/26";

#if ARDUINO < 100
#include <WProgram.h>                              // Add other libraries on demand as requested
#else
#include <Arduino.h>                               // Needed when working with libraries
#endif

#include <OneWire.h>

/***  Declare constants and variables for the serial monitor  ***/
int debug                              =  1;       // DEBUG counter; if set to 1, will write values back via serial
const unsigned int baudRate            =  9600;    // Baud rate for the serial monitor

/***  Declare constants and variables for the DS18x20  ***/
OneWire  ds(10);  // on pin 10

/**********************************************************************************************************/
/**********************************************************************************************************/
void setup(void) {
  /***  Optional Debug routine via serial monitor  ***/
  if (debug) {                                     // If we want to see some values for debugging in general...
    /***  Start class Serial with function/method begin(9600)  ***/
    /***  Instance variable .dot operator. method  ***/
    Serial.begin(baudRate);                        // ...set up the serial output on 0004 style
  }                                                // End of debug loop
  /***  Show software release  ***/
  Serial.print(author);
  Serial.print("\t");
  Serial.print(revision);                         
  Serial.print("\t");
  Serial.println(date);
  Serial.println();                                // Print empty line

  /***  Constants and variables for the temperature sensor  ***/


}                                                  // End of void setup
/**********************************************************************************************************/
/**********************************************************************************************************/
void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit, kelvin;
  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }

  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return;
  }
  Serial.println();

  /***  The first ROM byte indicates which chip  ***/
  switch (addr[0]) {
  case 0x10:
    Serial.println("  Chip = DS18S20");            // or old DS1820
    type_s = 1;
    break;
  case 0x28:
    Serial.println("  Chip = DS18B20");
    type_s = 0;
    break;
  case 0x22:
    Serial.println("  Chip = DS1822");
    type_s = 0;
    break;
  default:
    Serial.println("Device is not a DS18x20 family device.");
    return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);                                // start conversion, with parasite power on at the end

  delay(1000);                                     // maybe 750ms is enough, maybe not
  /***  We might do a ds.depower() here, but the reset will take care of it.  ***/

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);                                  // Read Scratchpad

  Serial.print("  Data = ");
  Serial.print(present,HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {                       // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  /***  Convert the data to actual temperature  ***/
  unsigned int raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3;                                // 9 bit resolution default
    if (data[7] == 0x10) {
      /***  Count remain gives full 12 bit resolution  ***/
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } 
  else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw << 3;               // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw << 2;          // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw << 1;          // 11 bit res, 375 ms
    /***  default is 12 bit resolution, 750 ms conversion time  ***/
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  kelvin = (celsius+273.15);
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius / ");
  Serial.print(fahrenheit);
  Serial.print(" Fahrenheit / ");
  Serial.print(kelvin);
  Serial.println(" Kelvin");

}                                                  // End of void loop
/**********************************************************************************************************/
/**********************************************************************************************************/
/***  Optional functions  ***/

/**********************************************************************************************************/
/**********************************************************************************************************/


