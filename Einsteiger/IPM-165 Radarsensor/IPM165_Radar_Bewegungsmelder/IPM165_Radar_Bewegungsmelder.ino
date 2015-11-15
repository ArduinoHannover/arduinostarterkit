/*******************************************************************************/
/* IPM165_Radar_Bewegungsmelder - Sehr empfindlicher Bewegungsmelder mit 
 * einem 24GHz Doppler-Radarsensor inkl. 73dB Verstärker Modul von InnoSenT. 
 * Die analoge Ausgangsspannung ohne Bewegung beträgt etwa 2,5V.
 * Mit einem detektierten Objekt, Rechtecksignal zwischen GND und etwa 3,5V.
 *
 *                       !Achtung!
 * Das Modul darf keinesfalls verpolt angeschlossen werden! Auch ist der Sensor
 * laut Hersteller InnoSenT extrem ESD-empfindlich! Aufgrund der hohen 
 * Verstärkung benötigt der Radarsensor unbedingt auch eine sehr stabile 
 * 5V Spannungsversorgung!
 *
 * Getestet mit:         Arduino Uno
 *                       Arduino IDE 1.63 / 1.64
 *
 * Referenz:             www.weidmann-elektronik.de/index.php?option=com_content&view=section&layout=blog&id=17&Itemid=21
 *
 * Original Autor:       http://shop.weidmann-elektronik.de/media/files_public/d8b2f188f3665f85c65fc762de61a095/Radarsensor165%20Arduino%20Example.pdf
 *                       
 * Autor:                Weidmann Elektronik GmbH
 *                       Dr. Ing. Wolfgang Weidmann
 *
 * Modifiziert von:      http://arduino-hannover.de/
 *                       Arduino Treffpunkt Hannover
 * Autor:                Olaf Meier
 *                       https://electronicfreakblog.wordpress.com/
 *
 * Hardware Verbindung:  Ardu  -  IPM165 Doppler-Radarsensormodul mit Amp.
 *                       +5V   -  Vcc
 *                       A5    -  Sout / Radarsignal digital 3,5V
 *                       GND   -  GND
 *
 * Ergänzungen:          -
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "IPM165Bewegung";
const char* revision              =  "R.1.1";
const char* author                =  "Olaf Meier";
const char* date                  =  "2015/11/15";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const byte radarPin               =  A5;           // Signalpin Sout
const byte ledPin                 =  13;           // Kontroll-LED
int sensorValue                   =  0;            // Sensorwert
/***  Schaltschwelle muss oberhalb 2,5V und unterhalb 3,5V sein  ***/
int threshold                     =  650;          // Schaltschwelle 575-750

/*******************************************************************************/
/*******************************************************************************/
void setup() {
  // pinMode(radarPin, INPUT);                     // Hier nicht notwendig
  pinMode(ledPin, OUTPUT);                         // Kontroll LED intern Pin 13
  digitalWrite(ledPin, LOW);                       // Kontroll LED ausschalten
}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  sensorValue = analogRead(radarPin);
  if (sensorValue > threshold)                     // Objekt erkannt
  {
    digitalWrite(ledPin, HIGH);                    // Kontroll LED einschalten
    delay(10);                                     // Verbesserung der Anzeige
  }
  else
    digitalWrite(ledPin, LOW);                     // Kontroll LED einschalten
}                                                  // Ende Loop (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Optionale Funktion:   ***/

/*******************************************************************************/
/*******************************************************************************/




