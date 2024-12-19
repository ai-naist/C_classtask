const int tempSensor = 0;
const int buzzerPin = 13;
#define NOTE_C6 1047

void setup()
{
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    int v_raw;
    float voltage, degreesC;

    v_raw = analogRead(tempSensor);
    voltage = (float)v_raw * (5.0 / 1023);
    degreesC = 100 * (voltage - 0.5);

    if (degreesC >= 30)
    {
        tone(buzzerPin, NOTE_C6, 100);
    }
    else
        digitalWrite(buzzerPin, LOW);

    Serial.print("Temperature: ");
    Serial.print(degreesC);
    Serial.print(" \xB0");
    Serial.print("C\n");
    delay(500);
}