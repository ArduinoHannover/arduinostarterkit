/*******************************************************************************/
/* LM35Simple - Ausgabe der sukzessive aufbereiteten Sensorwerte eines LM35DZ
 * Temperatursensors über den seriellen Monitor von knapp 0°C bis +100°C.
 *
 * Getestet mit:         Arduino Uno
 *                       Arduino IDE 1.63/1.64
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
 * Hardware Verbindung:  Ardu  -  LM35
 *                       +5V   -  1 Vs
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
const char* sketchname            =  "LM35SimpleI";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2015/11/11";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate
const byte TEMPSIGNALPIN          =  A5;           // Sensorsignal an Analogpin A5

/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Starte den seriellen Monitor und warte jetzt auf Daten zur Ausgabe  ***/
  Serial.begin(9600);                              // Starte seriellen Monitor

}                                                  // Ende der Setup Routine (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  int value = analogRead(TEMPSIGNALPIN);           // LM35 Sensorwert einlesen
  delay(1000);                                     // 1s Verzögerung zwecks Anzeige 

  Serial.println("--------------------------");    // Trennlinie mit jeder Messung
  Serial.print("Digitalwert AD-Wandler: ");
  Serial.println(value);                           // Wert AD-Wandler 0 bis 1023

  Serial.print("Eingangsspannung: ");
  float milliVolt = (value * 5000.0) / 1024.0;       // Berechne Messung in mV
  Serial.print(milliVolt);
  Serial.println("mV");

  Serial.print("Temperatur: ");
  float celsius = milliVolt / 10;                  // 10mV entsprechen 1°C
  Serial.print(celsius);
  Serial.println(" Celsius");
}                                                  // Ende der Loop Routine (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Optionale Funktion:   ***/

/*******************************************************************************/
/*******************************************************************************/




