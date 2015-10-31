/*** Blink Sketch ***/

const byte LED = 13;

void setup ()
{
    // Pin 13 als Ausgabe
    pinMode (LED, OUTPUT);
}

void loop ()
{
    digitalWrite (LED, HIGH);  // LED ein
    delay (1000);              // eine Sekunde warten
    digitalWrite (LED, LOW);   // turn the LED off by making the voltage LOW
    delay (1000);              // wait for a second
}
