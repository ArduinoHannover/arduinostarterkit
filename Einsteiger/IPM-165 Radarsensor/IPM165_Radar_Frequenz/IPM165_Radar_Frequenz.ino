/*******************************************************************************/
/* IPM165_Radar_Frequenz - Frequenzsmessung des Ausgangssignales
 * eines 24GHz Doppler-Radarsensor inkl. 73dB Verstärker Modul von InnoSenT.
 * Die analoge Ausgangsspannung ohne detektierte Bewegung beträgt etwa 2,5V.
 * Mit einem detektierten Objekt Rechtecksignal zwischen GND und etwa 3,5V.
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
 * Original Autor:       Weidmann Elektronik GmbH
 *
 * Autor:                Dr. Ing. Wolfgang Weidmann
 *
 *
 * Modifiziert von:      http://arduino-hannover.de/
 *                       Arduino Treffpunkt Hannover
 * Autor:                Olaf Meier
 *                       https://electronicfreakblog.wordpress.com/
 *
 * Hardware Verbindung:  Ardu  -  IPM165 Doppler-Radarsensormodul mit Amp.
 *                       +5V   -  Vcc
 *                       A5    -  Sout / Radarsignal digital 3,5V
 *                       D19   -  Sout (D19 entspricht A5)
 *                       GND   -  GND
 *
 * Ergänzungen:          Umrechnung der Frequenz in eine Geschwindigkeit
 *                       Mittelwertbildung der berechneten Werte
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "IPM165Frequenz";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2015/11/15";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate

const byte radarPin               =  A5;           // Messeingang Analog Sout
const int inputPin                =  19;           // Messeingang Digital Sout

const byte ledPin                 =  13;           // Kontroll-LED
int sensorValue                   =  0;            // Sensorwert
int threshold                     =  650;          // Schaltschwelle 575-750

unsigned long T                   =  0;            // Periodendauer in us
float f                           =  0.0;          // Frequenz in Hz

/*******************************************************************************/
/*******************************************************************************/
void setup() {
  Serial.begin(9600);                              // Starte seriellen Monitor

  pinMode(ledPin, OUTPUT);                         // Kontroll LED intern Pin 13
  digitalWrite(ledPin, LOW);                       // Kontroll LED ausschalten
}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {

  /***  Periodendauer des Eingangssignals an A5 / D19 berechnen  ***/
  T = pulseIn(inputPin, HIGH) + pulseIn(inputPin, LOW);// Periodendauer
  if (T == 0)                                      // Ohne Signal
  {
    Serial.println("Kein Dopplersignal");          // Timeout ohne Signal
  }
  else
  {
    f = 1 / (float)T;                              // Frequenz in MHz f=1/T
    f *= 1000000;                                  // Umrechnung in Hz * 1e6
    Serial.println(f);                             // Ausgabe der Frequenz
  }

  /***  Steuerung der Kontroll LED  ***/
  sensorValue = analogRead(radarPin);
  if (sensorValue > threshold)                     // Objekt erkannt
  {
    digitalWrite(ledPin, HIGH);                    // Kontroll LED einschalten
    delay(10);                                     // Verbesserung der Anzeige
  }
  else
    digitalWrite(ledPin, LOW);                     // Kontroll LED ausschalten
}                                                  // Ende Loop (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Optionale Funktion:   ***/

/*******************************************************************************/
/*******************************************************************************/




