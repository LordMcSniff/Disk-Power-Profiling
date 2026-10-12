#include <Arduino.h>
#include <Wire.h>
#include <INA226.h>


#define PIN_ONBOARD_LED 2

#define PIN_PS_ON_S8050 27
#define PIN_PWR_GOOD 26

#define PWR_GOOD_DIVIDER_R1 10000.0
#define PWR_GOOD_DIVIDER_R2 20000.0

#define SDA_1 23
#define SCL_1 22
#define SDA_2 19
#define SCL_2 18

TwoWire I2C_1 = TwoWire(0);
TwoWire I2C_2 = TwoWire(1);

INA226 ina_1(0x40, &I2C_1);
INA226 ina_2(0x40, &I2C_2);

void Panic(const char *message)
{
    Serial.println(message);
    while (1) {
        digitalWrite(PIN_ONBOARD_LED, HIGH);
        delay(100);
        digitalWrite(PIN_ONBOARD_LED, LOW);
        delay(100);
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(PIN_ONBOARD_LED, OUTPUT);
    digitalWrite(PIN_ONBOARD_LED, LOW);
    pinMode(PIN_PS_ON_S8050, OUTPUT);
    digitalWrite(PIN_PS_ON_S8050, LOW);
    pinMode(PIN_PWR_GOOD, INPUT);

    I2C_1.begin(SDA_1, SCL_1, 400000);
    I2C_2.begin(SDA_2, SCL_2, 400000);

    if (!ina_1.begin() || !ina_2.begin()) {
        Panic("Error initializing INA226 sensors!");
    }

    // TODO: completely configure INAs; eg. set sample averaging & conversion times, etc
    // TODO: move values into constexpr or #define
    int error = 0;
    error = ina_1.setMaxCurrentShunt(0.8, 0.1); // e.g., 0.8A max, 100 mOhm shunt
    if (error) {
        Serial.print("ina_1.setMaxCurrentShunt: ");
        Serial.println(error, HEX);
        Panic("Error configuring INA1");
    }
    error = ina_2.setMaxCurrentShunt(0.8, 0.1); // e.g., 0.8A max, 100 mOhm shunt
    if (error) {
        Serial.print("ina_2.setMaxCurrentShunt: ");
        Serial.println(error, HEX);
        Panic("Error configuring INA2");
    }
    Serial.println("INA226 sensors initialized with 0.8A max and 0.1Ω shunt.");

    delay(250);
    float v1 = ina_1.getBusVoltage();
    float i1 = ina_1.getCurrent_mA();
    float v2 = ina_2.getBusVoltage();
    float i2 = ina_2.getCurrent_mA();
    Serial.print("Initial Sensor Readings (");
    Serial.print(millis());
    Serial.println(" ms):");
    Serial.print("INA1 - Voltage: ");
    Serial.print(v1);
    Serial.print(" V, Current: ");
    Serial.print(i1);
    Serial.println(" mA");
    Serial.print("INA2 - Voltage: ");
    Serial.print(v2);
    Serial.print(" V, Current: ");
    Serial.print(i2);
    Serial.println(" mA");

    // delay(1000);
    Serial.println("Press any key to start the power supply...");
    while (Serial.available() == 0) {
        delay(10);
    }

    Serial.print("Starting Power Supply (");
    Serial.print(millis());
    Serial.println(" ms)\n");
    digitalWrite(PIN_PS_ON_S8050, HIGH);
}

void loop()
{
    float v1 = ina_1.getBusVoltage();
    float i1 = ina_1.getCurrent_mA();
    float v2 = ina_2.getBusVoltage();
    float i2 = ina_2.getCurrent_mA();
    bool pg = digitalRead(PIN_PWR_GOOD);

    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer),
                       "%8lu ms, %8.3f V, %8.3f mA, %8.3f V, %8.3f mA, %8s\n", millis(), v1, i1, v2,
                       i2, pg ? "TRUE" : "FALSE");

    Serial.write((uint8_t *)buffer, len);

    delay(10);
}
