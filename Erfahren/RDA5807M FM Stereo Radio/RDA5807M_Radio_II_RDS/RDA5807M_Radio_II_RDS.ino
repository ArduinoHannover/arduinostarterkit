/*******************************************************************************/
/* RDA5807M_Radio_II_RDS - Die Ausgabe der im setup() erkannten I2C Adressen des
 * (RRD-102 module)      Radiomodules wie auch alle weiteren Ausgaben erfolgen
 *                       über den seriellen Monitor.
 *                       Im setup() erfolgt nun auch eine erste Initialisierung
 *                       des RDA5807M ICs im sequentiellen Mode unter der
 *                       I2C-Adresse 0x10.
 *                       Der erste Radiosender sollte jetzt im Kopfhörer bzw.
 *                       über den Verstärker oder Aktivboxen zu hören sein.
 *                       Eine rudimentäre RDS Abfrage erfolgt über die Abfrage 
 *                       der Register 0x0C, 0x0D, 0x0E und 0x0F in  der loop()
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
 * Hardware Verbindung:  Arduino  -   RDA5807M Modul (RRD-102 module)
 *                       A4       -   06 SDA (I2C) 4,7k Pullup an +3,3V
 *                       A5       -   07 SCK (I2C) 4,7k Pullup an +3,3V
 *                       +3,3V    -   10 +3,3V
 *                       GND      -   01 GND
 *                                    05 Antenne (etwa 75cm lang)
 *                                    02 Kopfhörerausgang Links
 *                                    03 Kopfhörerausgang Rechts
 *
 *                                    RDA5807M Modul
 *                                    Ansicht von oben
 *                                    --------------
 *                                    |06        05|
 *                                    |07        04|
 *                                    |08        03|
 *                                    |09 ------ 02|
 *                                    |10|      |01|
 *                                    ----      ----
 *
 * Ergänzungen:          Auswertung des RDS Block B im nächsten Release
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "RDA5807M_Radio_II_RDS";
const char* revision              =  "R.1.1";
const char* author                =  "Olaf Meier";
const char* date                  =  "2016/01/27";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  19200;        // Serieller Monitor Baud Rate
const bool debugOutput            =  true;         // Set true for serial debug

#include <Wire.h>                                  // Einbindung der I2C-Library

/***  Bei dem RDA5807M wird hier der sequentielle Mode verwendet  ***/
const uint8_t RDA5807_ADR_T       =  0x60;         // I2C-Adresse TEA5767 access
const uint8_t RDA5807_ADR_R       =  0x11;         // I2C-Adresse Random access
const uint8_t RDA5807_ADR_S       =  0x10;         // I2C-Adresse Sequential access

/***  Variable für die RDS Rohdaten aus Block A, B, C und D  ***/
uint8_t rawRDS;                                    // Temporäre RDS Rohdaten 

/***  Berechnung der Kanalnummer  ***/ 
uint16_t channel = 179;                            // 104.90MHz Radio 21
/* Die Berechnung der Kanalnummer ist abhängig vom Kanalraster und dem
 * Bandbeginn. Angenommen das gewählte FM-Band beginnt bei 87,00 MHz und
 * das Kanalraster ist mit 100kHz eingestellt, (per Default) so ergibt sich
 * folgende Berechnung:
 * channel = (<gewünschte Frequenz in MHz> - 87.0MHz) / 0.1
 * Um nicht mit Bruchzahlen rechnen zu müssen, werden Zähler und Nenner
 * einfach mit 10 mulitpliziert. Daraus ergibt sich nach Kürzung:
 *
 * channel = (<gewünschte Frequenz in MHz> * 10) - 870MHz
 *
 * Kanalbeispiele aus dem Raum Hannover
 * channel   6 dec =  87.6 MHz  Hannover
 * channel  16 dec =  88.6 MHz  NDR Info
 * channel  39 dec =  90.9 MHz  NDR1
 * channel  56 dec =  92.6 MHz  N-Joy
 * channel  70 dec =  94.0 MHz  Deutschlandfunk
 * channel  92 dec =  96.2 MHz  NDR2
 * channel 149 dec = 101.9 MHz  FFN
 * channel 168 dec = 103.8 MHz  Antenne
 * channel 179 dec = 104.9 MHz  Radio21
 * channel 195 dec = 106.5 MHz  LeineHz
 * channel 204 dec = 107.4 MHz  Klassikradio
 */

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
  /*****************************************************************************/
  /***  Beginne die Initialisierung des Chips ***/
  Serial.println("\nInitialisierung des FM Radios RDA5807M...");
  Wire.beginTransmission(RDA5807_ADR_S);           // 0x10 Sequentieller Mode
  /***  Die Wire-Library überträgt immer nur 8-bit als 1 Byte! Daher werden  ***/
  /***  jeweils 2 Übertagungen für jedes der 16-Bit Register benötigt!  ***/
  /***  Zuerst wird das HighByte, danach das LowByte gesendet bzw. empfangen ***/
  Wire.write(0xC0);                                // 1. Register 0x02
  Wire.write(0x03);                                // 1. Register 0x02
  Wire.write(0x00);                                // Register 0x03 HighByte
  Wire.write(0x00);                                // Register 0x03 LowByte
  Wire.write(0x0A);                                // Register 0x04 HighByte
  Wire.write(0x00);                                // Register 0x04 LowByte
  Wire.write(0x88);                                // Register 0x05 HighByte
  Wire.write(0x0F);                                // Register 0x05 LowByte
  Wire.write(0x00);                                // Register 0x06 HighByte
  Wire.write(0x00);                                // Register 0x06 LowByte
  Wire.write(0x42);                                // Register 0x07 HighByte
  Wire.write(0x02);                                // Register 0x07 LowByte
  Wire.endTransmission();                          // Beende I2C Übertragung
  Serial.println(".............................Initialisierung beendet!");
  /*****************************************************************************/
  /***  Beginne die Senderabstimmung  ***/
  Serial.println("\nBeginne Senderabstimmung...");
  Wire.beginTransmission(RDA5807_ADR_S);           // 0x10 Sequentieller Mode
  /***  Nach Initialisierung, Reset löschen, dann Sendertuning  ***/
  Wire.write(0xC0);                                // 1. Register 0x02 HighByte
  Wire.write(0x01);                                // 1. Register 0x02 LowByte

  uint16_t chanHighByte = channel >> 2;            // Obere 8 bit
  Wire.write(chanHighByte);                        // Register 0x03 HighByte

  uint16_t chanLowByte = ((channel & 0b11) << 6 ) | 0b00010000;// Untere 8 bit
  Wire.write(chanLowByte );                        // Register 0x03 LowByte

  Wire.endTransmission();                          // Beende I2C Übertragung

  Serial.print("Abstimmung Kanal: ");
  Serial.print(channel);
  /***  Zurückrechnen der gewünschten Frequenz aus der Kanalnummer  ***/
  uint32_t freq = (100000 * channel) + 87000000;
  Serial.print(" Empfangsfrequenz: ");
  Serial.print(freq);
  Serial.println("Hz");
  Serial.println(".............................Senderabstimmung beendet!");
  /*****************************************************************************/
  /***  I2C Random Access Adresse 0x11 um RDS Modul im RDA5807M aktivieren  ***/
  Wire.beginTransmission(RDA5807_ADR_R);           // I2C Adresse 0x11 Random
  Wire.write(0x02);                                // Register 0x02 auswählen
  Wire.write(0xC0);                                // Wert 0xC0 ins 0x02 HighByte
  Wire.write(0x09);                                // 0x09 (RDS ein) ins 0x02
  Wire.endTransmission();
  /*****************************************************************************/

}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {

  /*****************************************************************************/
  Wire.beginTransmission(RDA5807_ADR_R);           // I2C Adresse 0x11 Random
  Wire.write(0x0C);                                // RDSA adress 0x0C
  Wire.endTransmission(0);                         // Neustart
  /***  Lese nun die folgenden 8 Byte aus den 4 RDS Registern RDSA - RDSD   ***/
  Wire.requestFrom(RDA5807_ADR_R, 8, 1);
  /*****************************************************************************/
  Serial.print("Block A, 16 Bit PI Program Identification = Senderkennung: 0x");
  rawRDS = Wire.read();
  if (rawRDS <= 0x0F) Serial.print("0");           // Zeige BLock A PI HighByte
  Serial.print(rawRDS, HEX);

  rawRDS = Wire.read();
  if (rawRDS <= 0x0F) Serial.print("0");           // Zeige Block A PI LowByte
  Serial.println(rawRDS, HEX);

  Serial.print("Block B mit 4 Bit GT, TA, TP, PTY, 5 Bit Daten je nach GT: 0x");
  rawRDS = Wire.read();
  if (rawRDS <= 0x0F) Serial.print("0");           // Zeige Block B (PTY, TP, GT) HighByte
  Serial.print(rawRDS, HEX);

  rawRDS = Wire.read();
  if (rawRDS <= 0x0F) Serial.print("0");           // Zeige Block B (PTY, TP, GT) LowByte
  Serial.print(rawRDS, HEX);
  Serial.println(" ");

  Serial.println("Inhalt abhaengig von GT Block B. Dynamischer Block C and D:");
  Serial.write(Wire.read());                       // Zeige die nächsten 4 Bytes im Klartext
  Serial.write(Wire.read());
  Serial.write(Wire.read());
  Serial.write(Wire.read());
  Serial.print("\r\n\r\n");
  Wire.endTransmission();                          // Ende der I2C Übertragung
  /*****************************************************************************/


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
  Serial.println(".............................Scan beendet!");
}                                                  // Ende I2C_Scanner
/*******************************************************************************/
/*******************************************************************************/




