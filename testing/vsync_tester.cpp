#include <Arduino.h>

// #define OFF 0
// #define ON 1
// #define PIN_SENSOR A0
// #define PIN_CLICK 2
// #define PIN_STATE 12

#define OFF 0
#define ON 1
#define PIN_SENSOR 36
#define PIN_SENSOR_2 25
#define PIN_CLICK 19
// #define PIN_STATE 3
#define PIN_LED_CLICK 18
#define PIN_LED_THRESH 23
#define PIN_LED_THRESH_2 5

#define MODE_IDLE 0
#define MODE_CALIBRATE 1
#define MODE_MEASURE 2
#define MODE_SEND 3
#define MODE_ON 4
#define MODE_TEST 5

int MODE = MODE_IDLE;

int threshold = -1;
int threshold2 = -1;

unsigned long last_measurement;

void sleep()
{
    delay(random(500, 1500));
    delayMicroseconds(random(0, 1000));
}

int calibrate()
{
    long blackValue = -1;
    long whiteValue = -1;
    long blackValue2 = -1;
    long whiteValue2 = -1;
    long success = 1;

    blackValue = analogRead(PIN_SENSOR);
    blackValue2 = analogRead(PIN_SENSOR_2);

    digitalWrite(PIN_CLICK, HIGH);
    digitalWrite(PIN_LED_CLICK, HIGH);
    delay(500);

    whiteValue = analogRead(PIN_SENSOR);
    whiteValue2 = analogRead(PIN_SENSOR_2);

    digitalWrite(PIN_CLICK, LOW);
    digitalWrite(PIN_LED_CLICK, LOW);
    delay(500);

    // threshold = whiteValue - ((whiteValue - blackValue) / 2);
    threshold = blackValue - ((blackValue - whiteValue) / 2);
    threshold2 = blackValue2 - ((blackValue2 - whiteValue2) / 2);

    Serial.print("# b: ");
    Serial.print(blackValue);

    Serial.print(", w: ");
    Serial.print(whiteValue);

    Serial.print(", t: ");
    Serial.print(threshold);

    Serial.print(", t2: ");
    Serial.print(threshold2);

    if (threshold < 100)
    {
        Serial.print("; error: low threshold");
        success = 0;
    }

    Serial.println();

    return success;
}

unsigned long measure()
{
    digitalWrite(PIN_CLICK, HIGH);
    digitalWrite(PIN_LED_CLICK, HIGH);
    unsigned long time = micros();
    unsigned long result;
    unsigned long result_2;

    bool thresh_1 = 0;
    bool thresh_2 = 0;

    while (1)
    {

        if (analogRead(PIN_SENSOR) < threshold && !thresh_1)
        {
            result = micros() - time;
            digitalWrite(PIN_LED_THRESH, HIGH);
            thresh_1 = 1;
        }

        if (analogRead(PIN_SENSOR_2) < threshold2 && !thresh_2)
        {
            result_2 = micros() - time;
            digitalWrite(PIN_LED_THRESH_2, HIGH);
            thresh_2 = 1;
        }

        if (thresh_1 && thresh_2)
        {
            thresh_1 = 0;
            thresh_2 = 0;

            delay(100);
            digitalWrite(PIN_CLICK, LOW);
            digitalWrite(PIN_LED_CLICK, LOW);

            while (analogRead(PIN_SENSOR) < threshold)
                delay(100);
            while (analogRead(PIN_SENSOR_2) < threshold2)
                delay(100);

            digitalWrite(PIN_LED_THRESH, LOW);
            digitalWrite(PIN_LED_THRESH_2, LOW);

            break;
        }

        yield();
    }

    return result - result_2;
}

void setup()
{
    pinMode(PIN_SENSOR, INPUT);
    pinMode(PIN_SENSOR_2, INPUT);
    pinMode(PIN_CLICK, OUTPUT);
    // pinMode(PIN_STATE, INPUT);
    pinMode(PIN_LED_CLICK, OUTPUT);
    pinMode(PIN_LED_THRESH, OUTPUT);
    pinMode(PIN_LED_THRESH_2, OUTPUT);

    Serial.begin(9600);

    // randomSeed(analogRead(A5));

    delay(100);
}

void loop()
{
    // Serial.println("Print:");
    // Serial.println(analogRead(PIN_SENSOR));
    // Serial.println(analogRead(PIN_SENSOR_2));
    // Serial.println("-----");
    // delay(100);
    // return;

    if (MODE == MODE_IDLE || MODE == MODE_ON || MODE == MODE_TEST)
    {
        char message = Serial.read();

        if (message == 'c')
            MODE = MODE_CALIBRATE;
        else if (message == 'm')
            MODE = MODE_MEASURE;
        else if (message == 's')
            MODE = MODE_SEND;
        else if (message == 'o')
        {
            if (MODE == MODE_ON)
            {
                MODE = MODE_IDLE;
                digitalWrite(PIN_CLICK, LOW);
            }
            else
            {
                MODE = MODE_ON;
                digitalWrite(PIN_CLICK, HIGH);
            }
        }
        else if (message == 't')
        {
            if (MODE == MODE_TEST)
            {
                MODE = MODE_IDLE;
                digitalWrite(PIN_CLICK, LOW);
            }
            else
            {
                MODE = MODE_TEST;
                sleep();
                digitalWrite(PIN_CLICK, HIGH);
            }
        }
    }
    else if (MODE == MODE_CALIBRATE)
    {
        randomSeed(millis());
        calibrate();
        MODE = MODE_IDLE;
    }
    else if (MODE == MODE_MEASURE)
    {
        sleep();
        last_measurement = measure();
        Serial.println(last_measurement);
        MODE = MODE_IDLE;
    }
    else if (MODE == MODE_SEND)
    {
        Serial.println(last_measurement);
        MODE = MODE_IDLE;
    }
    delay(50);
}
