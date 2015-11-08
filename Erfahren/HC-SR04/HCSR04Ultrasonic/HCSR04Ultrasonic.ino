/*******************************************************************************/
/* HCSR04Ultrasonic - Entfernungsmessung mit einem 4-pol. Ultraschallsensor HC-SR04. 
 * Entfernungen zwischen etwa 3cm and 300cm werden über den seriellen Monitor angezeigt.
 * 
 * Getestet mit:         Arduino Uno
 *                       Arduino IDE 1.63
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
 * Hardware Verbindung:  Ardu  -  HC-SR04  
 *                       +5V   -  1 Vcc
 *                       DP8   -  2 Trig
 *                       DP9   -  3 Echo
 *                       GND   -  4 GND
 * 
 * Ergänzungen:          Messgenauigkeit über einen zusätzlichen Temperatursensor erhöhen
 *                       Fehlermeldungen abfangen bei Werten ausserhalb des Messbereiches
 * 
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "HC-SR04 Ultrasonic";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2015/10/11";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate
const byte TRIGGERPIN             =  8;            // Trig pin 2 HC-SR04
const byte ECHOPIN                =  9;            // Echo pin 3 HC-SR04

/***  Berechne die Temperaturabhängigkeit der Ausbreitungsgeschwindigkeit in Luft  ***/
const int T                       =  20;           // Umgebungstemperatur -20°C - +40°C
float v                           =  331.5 + 0.606 * T;// Ausbreitungsgeschw. in m/s
/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Starte den seriellen Monitor und warte jetzt auf Daten zur Ausgabe  ***/
  Serial.begin(9600);                              // Starte seriellen Monitor
  pinMode(TRIGGERPIN, OUTPUT);                     // Trigger ist Ausgang
  pinMode(ECHOPIN, INPUT);                         // Echo ist Eingang
  digitalWrite(TRIGGERPIN, LOW);
}                                                  // Ende der Setup Routine (Einmalig) 
/*******************************************************************************/
/*******************************************************************************/
void loop() {

  Serial.print(v);  
  Serial.println(" m/s");                          // Zeige Ausbreitungsgeschwindigkeit

  float d = measureDistance();                     // Funktion zur Abstandsmessung aufrufen
  Serial.print(d);    
  Serial.println("cm");                            // Zeige berechneten Abstand
  delay(500);                                      // 2 Messzyklen je Sekunde
}                                                  // Ende der Loop Routine (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Funktion: Ultraschall-Abstandsmessung  ***/
float measureDistance() {
  digitalWrite(TRIGGERPIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERPIN, LOW);

  /***  Messung des Ausgangspulses am Echo-Eingang  ***/
  float durationMicroS = pulseIn(ECHOPIN, HIGH);   // Pulsdauer 150us bis 25ms (timeout 38ms)
  float duration = durationMicroS / 1000000.0;     // Umrechnung in Sekunden
  float distance = duration * v / 2;               // Distanz ist der einfache Weg des Schalls
  return distance * 100;                           // Rückgabewert Entfernung in cm

  }                                                // Ende der Funktion measureDistance()
/*******************************************************************************/
/*******************************************************************************/




