/*******************************************************************************/
/* RDA5807AddressScanner - Die Ausgabe der erkannten I2C Adressen des 
 *                       Radiomodules erfolgt über den seriellen Monitor.
 *                       
 *
 * Getestet mit:         Arduino Nano
 *                       Arduino IDE 1.65
 *
 * Referenz:             -
 *
 * Original Autor:       http://arduino-hannover.de/
 *                       Arduino Treffpunkt Hannover
 * Autor:                Olaf Meier
 *                       https://electronicfreakblog.wordpress.com/
 *
 * Modifiziert von:
 * Autor:
 *
 * Hardware Verbindung:  Arduino  -   RDA5807M Modul
 *                       A4       -   06 SDA (I2C) 4,7k Pullup an +3,3V
 *                       A5       -   07 SCK (I2C) 4,7k Pullup an +3,3V
 *                       +3,3V    -   10 +3,3V
 *                       GND      -   01 GND
 *                                    05 Antenne (etwa 75cm lang)
 *                                    02 Kopfhörerausgang Links
 *                                    03 Kopfhörerausgang Rechts
 *
 * Ergänzungen:          -
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "Sketch";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2016/01/24";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate

#include <Wire.h>                                  // Einbindung der I2C-Library

/***  Nach Komplexität sortierte I2C-Adresse; je nach verwendetem Mode  ***/
const uint8_t RDA5807_ADR_T       =  0x60;         // I2C-Adresse TEA5767 access
const uint8_t RDA5807_ADR_S       =  0x10;         // I2C-Adresse sequential access
const uint8_t RDA5807_ADR_R       =  0x11;         // I2C-Adresse random access

/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Starte den seriellen Monitor und warte jetzt auf Daten zur Ausgabe  ***/
  Serial.begin(BAUDRATE);                          // Starte seriellen Monitor
  while (!Serial);                                 // Leonardo spezifisch
  Serial.println("Arduino Treffpunkt Hannover");   // Textausgabe
  Serial.println("Arduino FM Radio mit RDA5807M Chip");

  Wire.begin();                                    // Intit I2C-Bus(2 Wire)
  I2C_Scanner();                                   // Scanne I2C-Adressbereich
}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {

  // Loop bleibt vorerst leer

}                                                  // Ende Loop (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Optionaler I2C Scanner  ***/
void I2C_Scanner()
{
  uint8_t I2Caddress;                              // I2C-Adressbereich 1..127
  uint8_t I2Cmessage;
  Serial.println();
  Serial.println("I2C Scanner - Starte Scan...");
  for (I2Caddress = 0; I2Caddress <= 127; I2Caddress++)
  {
    Wire.beginTransmission(I2Caddress);
    I2Cmessage = Wire.endTransmission();
    if (I2Cmessage == 0)                           // 0 == Geraet hat geantwortet
    {
      if (I2Caddress < 16) Serial.write('0');
      Serial.print("0x");
      Serial.print(I2Caddress, HEX);
      Serial.print(" OK ");
      switch (I2Caddress) {
        case RDA5807_ADR_T: Serial.println("RDA5807M im TEA5767 Mode"); break;
        case RDA5807_ADR_S: Serial.println("RDA5807M im sequentiellen Mode"); break;
        case RDA5807_ADR_R: Serial.println("RDA5807M im wahlfreien Mode"); break;
      }
    }
    else if (I2Cmessage == 4)                      // Gerät hat mit Fehler geantwortet
    {
      Serial.print("Unbekanntes Geraet bei Adresse 0x");
      if (I2Caddress < 16) Serial.print("0");
      Serial.println(I2Caddress, HEX);
    }
  }
  Serial.println("............................Scan beendet!");
}                                                  // Ende I2C_Scanner
/*******************************************************************************/
/*******************************************************************************/




