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
const byte TASTERPIN              =  8;            // Taster an Pin 8
const byte LEDPIN                 =  13;           // Interne LEDan Pin 13

/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Initialisierung der verwendeten IO-Pins ***/
  pinMode(TASTERPIN, INPUT);                       // Pin mit Taster als Eingang
  digitalWrite(TASTERPIN, HIGH);                   // Internen Pullup einschalten
  pinMode(LEDPIN, OUTPUT);                         // Pin mit LED als Ausgang
}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  /***  Kontinuierliche Abfrage, ob die Taste betätigt ist  ***/
  if (digitalRead(TASTERPIN) == LOW) {             // LOW wenn Taster betätigt ist
    digitalWrite(LEDPIN, HIGH);                    // Dann LED einschalten
  }
  else {                                           // HIGH wenn Taster nicht gedrückt
    digitalWrite(LEDPIN, LOW);                     // Dann LED ausschalten
  }
}                                                  // Ende Loop (Endlos)
/*******************************************************************************/
/*******************************************************************************/


