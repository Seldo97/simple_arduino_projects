const int resistorPin = A5;
const int potentiometerPin = A4;
const int ledPin = 8;

int brightness = 0;
int limit = 0;

String stringBright;
String stringLimit;

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    pinMode(resistorPin, INPUT);
    pinMode(potentiometerPin, INPUT);
}

void loop() {
    limit = map(analogRead(potentiometerPin), 0, 1020, 0, 100);
    brightness = map(analogRead(resistorPin), 0, 1020, 0, 100);;
    stringLimit = "Limit:" + String(limit);
    stringBright = "Brightness:" + String(brightness);
    Serial.println(stringLimit);
    Serial.println(stringBright);

    if (brightness < limit) {
        digitalWrite(ledPin, HIGH);
    }
    else {
        digitalWrite(ledPin, LOW);
    }

    delay(300);
}