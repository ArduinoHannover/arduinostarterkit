/*******************************************************************************/
/* BeruehrungssensorTTP224 - Bei Berührung eines der 4 Sensoren leuchtet die 
 *                       interne LED an Pin 13.
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
 * Hardware Verbindung:  Arduino  -  TTP224
 *                       ------------------
 *                       GND      -  GND
 *                       5V       -  Vcc
 *                       8        -  Sensor OUT1
 *                       9        -  Sensor OUT2
 *                       10       -  Sensor OUT3
 *                       11       -  Sensor OUT4

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
const char* date                  =  "2016/03/22";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const byte SENSORPIN1             =  8;            // Sensorausgang1 an Pin 8
const byte SENSORPIN2             =  9;            // Sensorausgang2 an Pin 9
const byte SENSORPIN3             =  10;           // Sensorausgang3 an Pin 10
const byte SENSORPIN4             =  11;           // Sensorausgang4 an Pin 11

const byte LEDPIN                 =  13;           // Interne LED an Pin 13

int sensorStatus                  =  0;            // Sensorstatus aller 4 Taster
/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Initialisierung der verwendeten IO-Pins ***/
  pinMode(SENSORPIN1, INPUT);                      // Pin mit Sensor1 als Eingang
  pinMode(SENSORPIN2, INPUT);                      // Pin mit Sensor2 als Eingang
  pinMode(SENSORPIN3, INPUT);                      // Pin mit Sensor3 als Eingang
  pinMode(SENSORPIN4, INPUT);                      // Pin mit Sensor4 als Eingang

  pinMode(LEDPIN, OUTPUT);                         // Pin mit LED als Ausgang
}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  /***  Abfrage aller 4 Sensoreingänge  ***/
  for (int i = 8; i <= 11; i++) {
    sensorStatus = digitalRead(i);
    /***  Prüfe ob eine der 4 Sensortasten betätigt worden ist  ***/
    if (sensorStatus == HIGH)                      // Ist ein Sensor aktiv?
      break;                                       // ...dann verlasse Schleife
  }
  /***  Wenn ein Sensor als aktiv detektiert worden ist, aktiviere LED  ***/
  if (sensorStatus == HIGH) {                      // HIGH wenn Sensor betätigt ist
    digitalWrite(LEDPIN, HIGH);                    // ...dann LED einschalten
  }
  else {                                           // LOW wenn Sensor nicht aktiv
    digitalWrite(LEDPIN, LOW);                     // Dann LED ausschalten
  }
}                                                  // Ende Loop (Endlos)
/*******************************************************************************/
/*******************************************************************************/


