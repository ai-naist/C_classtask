#include <LiquidCrystal.h>

const int tempSensor = 0;
const int buzzerPin = 13;
#define NOTE_C6 1047
#define NOTE_A6 1760

LiquidCrystal lcd(4, 6, 9, 10, 11, 12);

void setup()
{
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);

    lcd.begin(16, 2);
    lcd.clear();
}

void loop()
{
    int v_raw;
    float voltage, degreesC;

    v_raw = analogRead(tempSensor);
    voltage = (float)v_raw * (5.0 / 1023);
    degreesC = 100 * (voltage - 0.5);

    if ((degreesC >= 30) && (degreesC < 35))
    {
        tone(buzzerPin, NOTE_C6, 100);
    }
    else if (degreesC >= 35)
    {
        tone(buzzerPin, NOTE_A6, 100);
    }
    else
        digitalWrite(buzzerPin, LOW);

    Serial.print("Temperature: ");
    Serial.print(degreesC);
    Serial.print(" \xB0");
    Serial.print("C\n");

    String s = String(degreesC, 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(s);

    delay(500);
}