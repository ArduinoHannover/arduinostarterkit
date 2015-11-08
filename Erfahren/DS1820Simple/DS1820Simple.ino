/*******************************************************************************/
/* DS1820Simple - Ein einfacher Sketch um die Temperatur eines einzelnen DS1820
 * oder DS18S20 Sensors über den seriellen Monitor auszugeben. Die Verwaltung 
 * mehrerer Sensoren sowie die Auswertung negativer Temperaturen ist hier noch
 * nicht vorgesehen, um den Sketch so einfach wie möglich zu gestalten.
 *
 * Getestet mit:         Arduino Uno
 *                       Arduino IDE 1.63
 *
 * Referenz:             http://www.pjrc.com/teensy/td_libs_OneWire.html
 *
 * Original Autor:       Paul Stoffregen, Beispiel DS18x20_temperature
 *
 * Modifiziert von:      http://arduino-hannover.de/
 *                       Arduino Treffpunkt Hannover
 * Autor:                Olaf Meier
 *                       https://electronicfreakblog.wordpress.com/
 *
 * Hardware Verbindung:  Ardu  -  Sensor DS1820/DS18S20
 *                       GND   -  Pin 1
 *                       DP7   -  Pin 2 (4,7k Pullup verbunden mit 5V)
 *                       5V    -  Pin 3
 *                                 _____
 *                                /     \  Frontansicht auf Laserbeschriftung
 *                                -------
 *                                |  |  |
 *                                1  2  3
 *                                |  |  |
 *                               GND D Vdd
 *
 * Ergänzungen:          -
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "DS1820Simple";
const char* revision              =  "R.1.1";
const char* author                =  "www.arduino-hannover.de";
const char* creator               =  "Olaf Meier";
const char* date                  =  "2015/10/31";
/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate

#include <OneWire.h>                               // DS1820 Bibliothek einbinden 
const byte TEMPSENSORPIN          =  7;            // DS1820 Datenpin mit DP7 verbinden
OneWire oneWire(TEMPSENSORPIN);                    // Object onewire an DP7 erzeugen
/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Starte den seriellen Monitor. Warte jetzt auf Daten zur Ausgabe  ***/
  Serial.begin(BAUDRATE);
}                                                  // Ende der Setup Routine (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  oneWire.reset();                                 // Objekt oneWire zurücksetzen
  /***  Library Methode onWire.skip() sowie oneWire.write(0xCC) sind identisch  ***/
  /***  Funktioniert aber nur mit einem Sensor ohne explizite Adressabfrage  ***/
  oneWire.skip();                                  // Skip: ROM Abfrage überspringen
  //  oneWire.write(0xCC);                         // Skip: ROM Abfrage überspringen

  /***  Starte die Temperaturmessung innerhalb des Sensors  ***/
  oneWire.write(0x44);                             // Starte Temperaturkonvertierung
  /***  Um dem Sensor etwas Zeit zu geben, ist eine Verzögerung notwendig  ***/
  delay(1000);                                     // Verzögerung 1s

  boolean present = oneWire.reset();               // Ist ein Device angeschlossen?
  Serial.print("Sensor: ");                        // Anzeigen ob Sensor vorhanden
  Serial.println(present);                         // 1 = Device vorhanden

  /***  Library Methode onWire.skip() sowie oneWire.write(0xCC) sind identisch  ***/
  /***  Funktioniert aber nur mit einem Sensor ohne explizite Adressabfrage  ***/
  oneWire.skip();                                  // Skip: ROM Abfrage überspringen
  //  oneWire.write(0xCC);                         // Skip: ROM Abfrage überspringen

  /***  Die Daten aus dem Scratchpad des Sensors werden ausgelesen  ***/
  oneWire.write(0xBE);                             // Kommando Scratchpad auslesen
  /***  Schreibe die ersten beiden Bytes mit Temperatur davon in ein Array  ***/
  int data[2];                                     // Byte 0 = LSB; 1 = MSB
  for (byte i = 0; i < 2; i++) {                   // 2 Bytes in Array schreiben
    data[i] = oneWire.read();
  }

  /***  Temperaturberechnung. Byte 0 mit Wertigkeit 0,5 für das kleinste Bit  ***/
  float temperature = data[0] * 0.5;
    Serial.print("Es sind ");
    Serial.print(temperature);                     // Temperatur in °C ausgeben
    Serial.println (" C");
    Serial.println ();                             // Leerzeile

}                                                  // Ende der Loop Routine (Endlos)
/*******************************************************************************/
/*******************************************************************************/
