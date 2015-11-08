/*******************************************************************************/
/* DS1820Scanner - Dieser Sketch identifiziert die 64-bit Adressen von bis zu
 * 127 Stück der DS18xx Maxim (Dallas) 1-Wire Temperatursensoren DS1820,
 * DS18S20, DS18B20 wie auch DS1822. Die Erkennung erfolgt auch im Mischbetrieb!
 * Die jeweilige 8-Byte Adresse der Sensoren wird über den seriellen Monitor
 * ausgegeben. Das LOW-Byte enthält den Familiencode gefolgt von einer weltweit 
 * einmaligen 6-Byte langen Adresse und dem HIGH-Byte mit dem CRC.
 * Die Funktion findsensor wird nur einmal während der void setup() Routine
 * aufgerufen. Ein erneuter Suchlauf kann über den Reset-Taster erfolgen.
 *
 * Getestet mit:         Arduino Uno
 *                       Arduino IDE 1.63
 *
 * Referenz:             http://www.pjrc.com/teensy/td_libs_OneWire.html
 *
 * Original Autor:       Paul Stoffregen, Beispiel DS18x20_temperature
 *
 * Modifiziert von:      http://www.arduinio-hannover.de
 *                       Arduino Treffpunkt Hannover
 * Autor:                Olaf Meier
 *                       https://electronicfreakblog.wordpress.com/
*
 * Hardware Verbindung:  Ardu  -  Sensor DS18xx
 *                       GND   -  Pin 1
 *                       DP7   -  Pin 2 (4,7k pull-up verbunden mit 5V)
 *                       5V    -  Pin 3
 *                                 _____
 *                                /     \  Frontansicht auf Laserbeschriftung
 *                                -------
 *                                |  |  |
 *                                1  2  3
 *                                |  |  |
 *                               GND D Vdd
 *
 * Ergänzungen           -
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "DS18xxScanner";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2015/10/15";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate

#include <OneWire.h>                               // DS18xx Bibliothek einbinden
OneWire oneWire(7);                                // Objekt oneWire an DP7 erzeugen
/*******************************************************************************/
/*******************************************************************************/
void setup()
{
  Serial.begin(9600);                              // Starte seriellen Monitor
  findSensors();                                   // Funktion: Finde Sensoren
}                                                  // Ende Setup Routine (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop()
{
  /***  Restart über Reset-Taster  ***/
}                                                  // Ende Loop Routine (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Funktion: Finde alle 1-Wire DS18xx Sensoren. Anzeige der 8 ROM-Bytes  ***/
void findSensors()
{
  byte address[8];                                 // Store 8 ROM bytes of sensor
  byte noOfSensor = 0, i = 0, ok = 0, flag = 0;    // Diverse Hilfsvariablen
  Serial.println("DS18xx 1-Wire Temperatursensor Scanner");
  Serial.println();
  Serial.println("Suche...");
  Serial.println();
  /***  Das erste Byte enthält den Familiencode der hier ausgewertet wird  ***/
  while (oneWire.search(address))
  {
    Serial.println("-----------------------------------------------");
    Serial.print(noOfSensor += 1);
    Serial.print(". ");
    switch (address[0]) {
      case 0x10:
        Serial.println("Sensor ist ein DS18S20 oder aelterer DS1820: ");
        flag = true;                               //
        break;
      case 0x28:
        Serial.println("Sensor ist ein DS18B20: ");
        flag = true;                               //
        break;
      case 0x22:
        Serial.println("Sensor ist ein DS1822: ");
        flag = true;                               //
        break;
      default:
        Serial.println("Keinen gueltigen DS18xx Sensor gefunden!");
        return;
    }
    /***  Zeige alle 64 Adressbits sofern flag = 1 (true) ist, also alles OK  ***/
    if (flag == true)
    {
      if (OneWire::crc8(address, 7) != address[7])
      {
        Serial.println("CRC Pruefung nicht bestanden! Fehler!");
      }
      else
      {
        /***  Da bis hierhin alles Okay ist, zeige nun alle 8 Bytes  ***/
        for (i = 0; i < 8; i++)
        {
          Serial.print("0x");
          if (address[i] <= 0xF)                   // Führende 0 ggf. ergänzen
          {
            Serial.print("0");
          }
          Serial.print(address[i], HEX);           // Darstellung Hexadezimal
          if (i < 7)
          {
            Serial.print(", ");
          }
        }
        Serial.println("");
        ok = true;                                 // ok = 1
      }
    }                                              // Ende der if Schleife
  }                                                // Ende der while Schleife
  if (ok == false)                                 // ok=0, no valid sensor found
  {
    Serial.println("Keinen gueltigen DS18xx Sensor gefunden!");
  }
  Serial.println();
  Serial.println("Suche abgeschlossen! Druecke Reset Taster fuer Neustart.");
  Serial.println();
}                                                  // Ende der Funktion 
/*******************************************************************************/
/*******************************************************************************/

