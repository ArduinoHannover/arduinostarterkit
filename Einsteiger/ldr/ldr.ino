/* Photowiderstand
 *
 *  siehe auch: http://wiki.arduino-hannover.de/index.php?title=Fotowiderstand
 *
 *  2015-11-05   Andreas Dunker    erzeugt
 *
 **********************************************************************/

const byte INPUTPIN = 0; // analoger Pin 0 fuer den Eingang

void setup ()
{
    Serial.begin (9600);
}

void loop ()
{
    int wert = analogRead (INPUTPIN);  // Wert lesen
    Serial.println (wert);             // Wert ausgeben
    delay (1000);                      // ein wenig warten
}
