/*** Blink Sketch ***/
/**
 * Mit diesem Sketch wird eine LED im Sekundentakt ein und ausgeschaltet.
 * Nachfolgend wird der Pin der LED definiert, wobei Pin 13 meist mit der LED L auf dem Arduino verbunden ist.
*/
const byte LED = 13;
/*
 * Alternativ LED_BUILTIN als Konstante nutzen, die fuer jedes Board (sofern definiert) gueltig ist.
 * Sollte die LED bei dem von dir genutzen Board nicht an Pin 13 sein, so versuche es mit der Konstante.
 * Wenn du eine LED, die nicht auf dem Board selbst angebracht ist schalten moechtest, so nutze folgendes:
 * * Das kurze Bein (K, kurz, Kathode) der LED an GND (Ground/Masse/-)
 * * Das lange Bein (LAng, Anode) ueber einen Widerstand an den Pin, der durch LED definiert wurde.
 * Mehr Informationen zu LEDs: http://wiki.arduino-hannover.de/index.php?title=LED
*/

void setup ()
{
    // LED-Pin als Ausgang definieren, ansonsten ist ohne Definition der Pin als Eingang (INPUT)
    pinMode (LED, OUTPUT);
}

void loop ()
{
    digitalWrite (LED, HIGH);  // LED durch Schalten auf hohen Pegel (HIGH) einschalten
    delay (1000);              // eine Sekunde (1000 Millisekunden) warten
    digitalWrite (LED, LOW);   // LED durch Schalten auf niedrigen Pegel (LOW) ausschalten
    delay (1000);              // eine Sekunde warten
}
