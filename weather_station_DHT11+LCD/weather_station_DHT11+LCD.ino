#include <DHT.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
DHT dhtSensor; //DHT11
const int dhtSensorPin = 13;
const int lcdSize[] = { 16, 2 };
uint8_t degreeCharBitmap[] = { 0x6, 0x9, 0x9, 0x6, 0x0, 0, 0, 0 };

const int samplingRate = 15000;

float humidity = 0.0;
float temperature = 0.0;

void setup() {
    // Serial.begin(115200);
    dhtSensor.setup(dhtSensorPin);
    lcd.begin(lcdSize[0], lcdSize[1]);
    lcd.createChar(1, degreeCharBitmap);
    startupScreen();
}

void loop() {
    humidity = getHumidity();
    temperature = getTemperature();

    if (checkDhtSensorStatus()) {
        printData(temperature, humidity);
    }

    delay(dhtSensor.getMinimumSamplingPeriod() + samplingRate);
}

void printData(int temp, int hum) {
    lcd.setCursor(0, 0);
    lcd.print("Temp: " + String(temp) + "\001C");
    lcd.setCursor(0, 1);
    lcd.print("Hum: " + String(hum) + "%");
}

void startupScreen() {
    lcd.setCursor(5, 0);
    lcd.print("Hello!");
    lcd.blink();
    delay(3000);
    lcd.noBlink();
    lcd.clear();
}

float getTemperature() {
    return dhtSensor.getTemperature();
}

float getHumidity() {
    return dhtSensor.getHumidity();
}

boolean checkDhtSensorStatus() {
    return dhtSensor.getStatusString() == "OK";
}