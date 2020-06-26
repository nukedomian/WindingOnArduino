
#include <Wire.h>

void setup() {
    // initialize serial:
    Serial.begin(9600);
    // make the pins outputs:

    Serial.println("please input your instruction with 3 numbers");
}

void loop() {
    // if there's any serial available, read it:
    while (Serial.available() > 0) {

        // look for the next valid integer in the incoming serial stream:
        int x = Serial.parseInt();
        // do it again:
        int y = Serial.parseInt();
        // do it again:
        int t = Serial.parseInt();

        // look for the newline. That's the end of your sentence:
        if (Serial.read() == '\n') {
            Serial.print("x = ");
            Serial.println(x, DEC);
            Serial.print("y = ");
            Serial.println(y, DEC);
            Serial.print("t = ");
            Serial.println(t, DEC);
        }
    }
}