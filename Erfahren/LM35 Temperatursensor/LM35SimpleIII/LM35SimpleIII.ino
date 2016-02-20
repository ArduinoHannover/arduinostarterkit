/*******************************************************************************/
/* LM35SimpleIII - Nochmals verbesserte Ausgabe der Sensorwerte eines LM35DZ 
 * Temperatursensors von knapp 0°C bis +100°C über den seriellen Monitor.
 * Der Temperaturmesswert wird wieder Mal über mehrere Messzyklen kumuliert um 
 * darüber eine stabilere Anzeige zu erhalten. Um die Messgenauigkeit zu 
 * erhöhen, wird in diesem Sketch der Meßbereich des AD-Wandlers angepasst.
 * Der LM35 liefert eine Ausgangsspannung vom 0 bis 1V. Durch Anpassung des
 * Arbeitsbereiches des Arduino AD-Wandlers von ursprünglich 5V auf jetzt 
 * 1,1V. Durch Umschaltung der Referenzspannung von der 5V Betriebsspannung 
 * auf die interne 1,1V Referenzspannungsquelle kann der aktive 
 * Arbeitsbereich des Wandlers von 20% auf 90% optimiert werden!
 * Über einen Korrekturwert lässt sich der Sensor ggf. auch noch kalibrieren. 
 * 
 *
 * Getestet mit:         Arduino Uno
 *                       Arduino IDE 1.63/1.64
 *
 * Referenz:             https://www.arduino.cc/en/Reference/AnalogReference
 *
 * Original Autor:       http://arduino-hannover.de/
 *                       Arduino Treffpunkt Hannover
 * Autor:                Olaf Meier
 *                       https://electronicfreakblog.wordpress.com/
 *
 * Modifiziert von:
 * Autor:
 *
 * Hardware Verbindung:  Ardu  -  LM35
 *                       +5V   -  1 Vs (Vcc)
 *                       A5    -  2 Vout
 *                       GND   -  3 GND
 *                                 _____
 *                                /     \  Frontansicht auf Laserbeschriftung
 *                                -------
 *                                |  |  |
 *                                1  2  3
 *                                |  |  |
 *                               Vs  Vo GND
 *
 * Ergänzungen:          -
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "LM35SimpleIII";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2015/11/13";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate
const byte TEMPSIGNALPIN          =  A5;           // Sensorsignal an Analogpin A5
const int REF_MV                  =  1100;         // AD Referenzspannung 1,1V
const float CALIBRATETEMP         =  -2.0;         // Korrekturwert der Anzeige
/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Starte den seriellen Monitor und warte jetzt auf Daten zur Ausgabe  ***/
  Serial.begin(9600);                              // Starte seriellen Monitor

  /***  DEFAULT = 5V oder 3,3V je nach verwendeter Betriebsspanung  ***/
  analogReference(INTERNAL);                       // Interne Referenz auf 1,1V

}                                                  // Ende der Setup Routine (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  long averageValue = 0;                           // Speicher für Durchschnittswert
  byte measureCycles = 10;                         // Anzahl der Durchläufe
  /***  Starte Messreihe mit Anzahl Zyklen und Berechnung des Durchschnitts  ***/
  for (int i = 0; i < measureCycles; i++)
  {
    int value = analogRead(TEMPSIGNALPIN);         // LM35 Sensorwert einlesen
    averageValue += value;                         // Kumuliere Werte der Messreihe
    delay(1);                                      // Delay ist hier optional
  }
  averageValue /= measureCycles;                   // Berechne Durschnittswert 
  delay(990);                                      // Anzeige so einfacher lesbar

  Serial.println("------------------------------");// Trennlinie mit jeder Messung
  Serial.print("Gemittelter Wert AD-Wandler: ");
  Serial.println(averageValue);                    // Wert AD-Wandler 0 bis 1023

  float milliVolt = (averageValue * REF_MV)/1024.0;// Berechne Messwert in mV
  Serial.print("Eingangsspannung: ");
  Serial.print(milliVolt);
  Serial.println("mV");

  float celsius = milliVolt / 10;                  // 10mV entsprechen 1°C
  celsius += CALIBRATETEMP;                        // Kalibrierung der Temperatur
  Serial.print("Temperatur: ");
  Serial.print(celsius);
  Serial.println(" Celsius");

  float fahrenheit = (celsius*9)/5+32;             // Umrechnung in Fahrenheit
  Serial.print("Temperatur: ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
  
  float kelvin = celsius + 273.15;                 // Umrechnung in Kelvin
  Serial.print("Temperatur: ");
  Serial.print(kelvin);
  Serial.println(" Kelvin");
}                                                  // Ende der Loop Routine (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Optionale Funktion:   ***/

/*******************************************************************************/
/*******************************************************************************/




