/*******************************************************************************/
/* DS1820Temperature - Ein universeller Sketch zur Temperaturanzeige von bis
 * zu 127 1-Wire Sensoren der Baureihe DS1820, DS18S20, DS1822 und DS18B20 über
 * den seriellen Monitor. Bei der DS1820 Familie ist dabei eine 9-bit Auflösung
 * sowie 9 bis 12-bit beim DS18B20 Sensor berücksichtigt. Ein Mischbetrieb
 * verschiedener Sensoren obiger Baureihen ist problemlos möglich.
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
 *                       DP7   -  Pin 2 (4.7k Pullup verbunden mit 5V)
 *                       5V    -  Pin 3
 *                                 _____
 *                                /     \  Frontansicht auf Laserbeschriftung
 *                                -------
 *                                |  |  |
 *                                1  2  3
 *                                |  |  |
 *                               GND D Vdd
 *
 * Ergänzungen:          Erweiterung der Auflösung des DS1820 von 9 auf 12 Bit
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "DS1820Temperature";
const char* revision              =  "R.1.1";
const char* author                =  "www.arduino-hannover.de";
const char* creator               =  "Olaf Meier";
const char* date                  =  "01.11.2015";
/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate

#include <OneWire.h>                               // DS1820 Bibliothek einbinden 
const byte TEMPSENSORPIN          =  7;            // DS1820 Datenpin mit DP7 verbinden
OneWire oneWire(TEMPSENSORPIN);                    // Object oneWire an DP7 erzeugen
byte noOfSensor = 0;                               // Zähler für Anzahl Sensoren
/***  Im Sketch unterstützte 1-Wire Temperatursensoren Maxim DS18xx  ***/
const byte DS18S20ID              =  0x10;         // Family code of DS1820/DS18S20
const byte DS18B20ID              =  0x28;         // Family code of DS18B20
const byte DS1822ID               =  0x22;         // Family code of DS1822
/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Starte den seriellen Monitor und warte auf Daten zur Ausgabe  ***/
  Serial.begin(BAUDRATE);
  /***  Zeige einmalig allgemeine Informationen zum Sketch  ***/
  Serial.print(sketchname);
  Serial.print(" ");                               // Leerzeichen
  Serial.print(revision);
  Serial.print(" ");                               // Leerzeichen
  Serial.print(date);
  Serial.print("\n\r");                            // Neue Zeile, Return
  Serial.print(author);
  Serial.print("  ");  
  Serial.println(creator);
  Serial.print("\n\r");                            // Neue Zeile, Return
  /*****************************************************************************/
 /* Der nachfolgende Teil der Setup Routine ist optional und dient nur dem Test
  * verschiedener Auflösungen des DS18B20 Sensors. DS1820 und DS18S20
  * unterstützen diese Funktion nicht! Dieser Teil kann daher ignoriert werden.
  * Bei Verwendung eines DS18B20 kann die standardmäßige Auflösung von 12 Bit
  * auch auf 11, 10, oder 9 Bit reduziert werden. Ein Vorteil dabei ist die
  * geringere Konversionszeit des Sensors.
  * In Byte 4 des Scratchpads stehen zur Einstellung der Auflösung des Sensors
  * die Bits 5 (R0) und 6 (R1) zur Verfügung. Da die Daten im Scratchpad des 
  * Sensors flüchtig sind und hier nicht explizit ins EEPROM gerettet werden,
  * kann hier relativ gefahrlos experimentiert werden. Weitere Details sind 
  * dazu auch im Datenblatt zu finden. Bei dem Kommando müssen immer
  * 3 Bytes geschrieben werden, die Alarmschwellen der Temperatur HIGH und 
  * LOW sowie das Konfigurationsbyte mit den beiden Bits zur Einstellung der
  * gewünschten Auflösung.
  * Zur Vereinfachung des Sketches muss die Adresse des gewünschten Sensors 
  * manuell in das nachfolgende Array DS18B20ADDRESS[8] eingetragen werden.
  * Die nachfolgenden 6 Zeilen Code müssen nun dazu aktiviert werden sowie 
  * eine der letzten 4 Zeilen dieses Blockes mit der gewünschte Auflösung. Es
  * darf nur eine Auflösung aktiviert werden, die anderen bleiben auskommentiert!
  */
//const byte DS18B20ADDRESS[8]    = {0x28, 0x61, 0x4F, 0x51, 0x04, 0x00, 0x00, 0xA5};
//oneWire.reset();
//oneWire.select(DS18B20ADDRESS);                  // Select your desired device
//oneWire.write(0x4E);                             // Command to write Scratchpad
//oneWire.write(0x4B);                             // Write Alarm HIGH
//oneWire.write(0x46);                             // Write Alarm LOW
//oneWire.write(0x7F);                             // Schreibe 12-bit Konfiguration
//oneWire.write(0x5F);                             // Schreibe 11-bit Konfiguration
//oneWire.write(0x3F);                             // Schreibe 10-bit Konfiguration
//oneWire.write(0x1F);                             // Schreibe 9-bit Konfiguration
 /*
  *                                    MSB                    LSB
  *                           Bit:      7  6   5   4  3  2  1  0
  * Konfigurationsregister Byte 4:      0  R1  R0  1  1  1  1  1
  * 
  * Sollte wider Erwarten an dieser Stelle etwas doch nicht ganz klappen, so muss
  * nur kurz die Stromversorgung getrennt werden, um den Sensor mit seinen 
  * Standard Konfigurationsdaten mit 12-bit Auflösung neu zu starten.
  */
  /*****************************************************************************/
}                                                  // Ende der Setup Routine (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  byte i;                                          // Hilfsvariable für Schleife
  boolean present = false;                         // true wenn Sensor gefunden
  boolean typeOfSensor;                            // 1=DS1820/S20; 0=DS1822/B20
  byte data[9];                                    // Array für 9 Byte Scratchpad
  byte address[8];                                 // Array 8 Byte für ROM Adresse
  float celsius, fahrenheit;
  /***  Prüfe auf verfügbare Sensoren, schreibe Seriennummer in Adress Array  ***/
  if (!oneWire.search(address)) {                  // Suche nach allen DS18xx
    Serial.println();
    Serial.println("Keine weiteren Sensoren mit gueltiger Seriennummer gefunden!");
    Serial.println("------------------------------------------------------------");
    oneWire.reset_search();                        // Kein neuer Fund, Suche zurücksetzen
    delay(500);                                    // Verzögerung für bessere Lesbarkeit
    noOfSensor = 0;                                // Gerätezähler zurücksetzen
    return;
  }
  /***  Drucke alle ROM Codes und zeige Typ des Sensors, Addresse und CRC  ***/
  Serial.print(noOfSensor += 1);
  Serial.print(". ");
  Serial.print("ROM =");
  for (i = 0; i < 8; i++) {
    Serial.write(' ');                             // Leerzeichen
    /***  Zeige 0x für Hexwerte mit ggf. führender 0  ***/
    Serial.print("0x");
    if (address[i] <= 0xF)                         // Drucke führende 0
    {
      Serial.print("0");
    }
    Serial.print(address[i], HEX);                 // Drucke Hexwerte
  }
  /***  CRC von jedem Sensor auf Gültigkeit prüfen  ***/
  if (OneWire::crc8(address, 7) != address[7]) {
    Serial.println("CRC ungueltig!");
    return;
  }
  Serial.println();
  /***  Das erste ROM Byte enthält den Sensortyp und bestimmt damit  ***/
  /***  auch die Art und Weise der Temperaturauswertung  ***/
  switch (address[0]) {
    case DS18S20ID:
      Serial.println("  1-Wire Sensor ist DS1820/DS18S20");
      typeOfSensor = 1;                            // Typ 1 gemäß Byte 0
      break;
    case DS18B20ID:
      Serial.println("  1-Wire Sensor ist DS18B20");
      typeOfSensor = 0;                            // Typ 0 gemäß Byte 0
      break;
    case DS1822ID:
      Serial.println("  1-Wire Sensor ist DS1822");
      typeOfSensor = 0;                            // Typ 0 gemäß Byte 0
      break;
    default:
      Serial.println("Unbekannter Sensor!");
      return;
  }
  /*****************************************************************************/
  /***  Starte Konvertierung der Temperatur auch mit parasitärer Versorgung  ***/
  oneWire.reset();
  oneWire.select(address);
  oneWire.write(0x44, 1);                          // Temp.Konvertiertung, parasitär
  /***  Die Konvertierung der Temperatur im Sensor benötigt bis zu 750ms  ***/
  delay(1000);                                     // 750ms sollten auch reichen
  /***  Wähle Scratchpad anhand der ermittelten Adresse und lese Daten aus  ***/
  present = oneWire.reset();
  oneWire.select(address);
  oneWire.write(0xBE);                             // Kommando Lese Scratchpad
  /***  Zeige 9 Bytes des jeweiligen Scratchpads aller gefundenen Sensoren  ***/
  Serial.print("  Data = ");
  for ( i = 0; i < 9; i++) {                       // 9 Byte Array auslesen
    data[i] = oneWire.read();
    Serial.print(data[i], HEX);                    // Werte Hexadezimal anzeigen
    Serial.print(" ");                             // Leerstelle drucken
  }
  /***  Überprüfe CRC aller vom Scratchpad eingelesenen 9 Bytes  ***/
  Serial.print("  CRC = ");
  Serial.print(OneWire::crc8(data, 8), HEX);       // CRC Check (data, length) HEX
  Serial.println();
  /*****************************************************************************/
  /***  Berechnung der Temperatur aus HIGH-Byte 1 und LOW-Byte 0 (Temperatur)  ***/
  /***  Der Umrechnungsfaktor ist abhängig von Sensor und Auflösung  ***/
  float factor = 0.0;                              // Factor depends on device
  int16_t tmp;                                     // Store 16-bit raw temperature
  /***  Prüfe auf DS1820 oder DS18S20 und erzeuge eine 16-bit Int Variable  ***/
  if (typeOfSensor == 1) {                         // Nur bei DS1820 oder DS18S20
    tmp = ((data[1] << 8) + data[0]);              // Generiere ein 16-bit Int tmp
    factor = 0.5;                                  // 0.5°C / Bit bei 9 Bit Aufl.
    float temp = tmp * factor;                     // Berechne temp
  }
  /***  Wenn kein DS1820 / DS18S20, dann muss es ein DS1822 / DS18B20 sein  ***/
  else {                                           
    /***  Prüfe die beiden Flags Bit 5/6 mit der Auflösung im Byte 4  ***/
    byte resolutionBits = data[4] & B01100000;     // Maskiere Bit 5 und 6
    /***  Als Dezimalzahl 0, 32, 64 oder 96 sind folgende Maskierungen ***/
    /***  entsprechend einer 9-, 10-, 11- oder 12-bit Auflösung möglich  ***/
    /***  Unbenutzte Bits haben keinen definierten Status! Daher auf 0 setzen  ***/
    switch (resolutionBits) {
      case 0:
        Serial.println("  Auflösung ist 9 Bit!");
        data[0] = data[0] & B11111000;             // Maskiere Bits für 9 Bit Auflösung
        break;
      case 32:
        Serial.println("  Auflösung ist 10 Bit!");
        data[0] = data[0] & B11111100;             // Maskiere Bits für 10 Bit Auflösung
        break;
      case 64:
        Serial.println("  Auflösung ist 11 Bit!");
        data[0] = data[0] & B11111110;             // Maskiere Bits für 11 Bit Auflösung
        break;
      case 96:
        Serial.println("  Auflösung ist 12 Bit!"); // Volle 12-bit Auflösung
        break;
      default:
        Serial.println("  Unbekannte Auflösung!");
        break;
    }
    tmp = ((data[1] << 8) + data[0]);              // Generiere 16-bit Int tmp
    factor = 0.0625;                               // 12-bit = 0,0625°C / Bit
  }
  /***  Berechne die Temperatur basierend auf der festgestellten Auflösung  ***/
  float temp = tmp * factor;                       // Auflösung 9 bis 12 Bit 
  Serial.print("  Temperatur ist ");
  Serial.print(temp);
  Serial.print(" Celsius bzw. ");
  fahrenheit = temp * 1.8 + 32.0;
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
}                                                  // Ende der Loop Routine (Endlos)
/*******************************************************************************/
/*******************************************************************************/




