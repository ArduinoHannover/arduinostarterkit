/*******************************************************************************/
/* Taster - Bei Betätigung des Tasters leuchtet die interne LED an Pin 13
 *
 * Getestet mit:         Arduino Uno
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
 * Hardware Verbindung:  Arduino  -  Gerät
 *                       ------------------
 *                       8        -  Taster (anderen Kontakt mit GND verbinden)
 *
 * Ergänzungen:          -
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "Taster";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2016/03/21";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const byte TASTERPIN1             =  8;            // Sensorausgang1 an Pin 8
const byte TASTERPIN2             =  9;            // Sensorausgang2 an Pin 9
const byte TASTERPIN3             =  10;           // Sensorausgang3 an Pin 10
const byte TASTERPIN4             =  11;           // Sensorausgang4 an Pin 11
const byte LEDPIN                 =  13;           // Interne LED an Pin 13

int sensorStatus                  =  0;            // Sensorstatus aller 4 Taster

/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Initialisierung der verwendeten IO-Pins ***/
  pinMode(TASTERPIN1, INPUT);                      // Pin mit Sensor1 als Eingang
  pinMode(TASTERPIN2, INPUT);                      // Pin mit Sensor2 als Eingang
  pinMode(TASTERPIN3, INPUT);                      // Pin mit Sensor3 als Eingang
  pinMode(TASTERPIN4, INPUT);                      // Pin mit Sensor4 als Eingang

  pinMode(LEDPIN, OUTPUT);                         // Pin mit LED als Ausgang



}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  for (int i = 8; i <= 11; i++) {
    sensorStatus = digitalRead(i);
    /***  Prüfe ob eine der 4 Sensortasten betätigt worden ist  ***/
    if (sensorStatus == HIGH)                      // Ein Sensor aktiv?
      break;                                       // ...dann verlasse Schleife
  }

  /***  Kontinuierliche Abfrage, ob die Taste betätigt ist  ***/
  if (sensorStatus == HIGH) {                    // HIGH wenn Sensor betätigt ist
    digitalWrite(LEDPIN, HIGH);                    // Dann LED einschalten
  }
  else {                                           // LOW wenn Sensor nicht aktiv
    digitalWrite(LEDPIN, LOW);                     // Dann LED ausschalten
  }
}                                                  // Ende Loop (Endlos)
/*******************************************************************************/
/*******************************************************************************/


