#include <ESPAsyncWebServer.h>
#include <Joystick.h>
#include <unity.h>

void test_Power_Ground(void)
{
    int expectedGround = LOW;
    bool expectedPowerIsOn = true;
    int actualGround = analogRead(Joystick::pinGround);
    bool actualPowerIsOn = analogRead(Joystick::pinPower) > LOW;
}

int main()
{
    
}

void setup()
{
    Serial.begin(115200);
    Joystick::Setup();

    delay(1000);
    UNITY_BEGIN();
    RUN_TEST(test_Power_Ground);
    UNITY_END();
}

void loop() {}