#include <ESPAsyncWebServer.h>
#include <Joystick.h>
#include <WiFi_Helper.h>
#include <unity.h>

void test_Power(void)
{
    bool expected = LOW;
    bool actual = LOW;
    TEST_ASSERT_EQUAL(expected, actual);
}

void test_Ground()
{
    int expectedGround = LOW;
    int actualGround = analogRead(Joystick::pinGround);
    TEST_ASSERT_EQUAL(expectedGround, actualGround);
}

void test_WiFi(void)
{
    int expected = true;
    int actual = WiFi_Helper::isUp;
    TEST_ASSERT_EQUAL(expected, actual);
}

int main()
{
}

void setup()
{
    Serial.begin(115200);
    Joystick::Setup();
    WiFi_Helper::Setup();

    delay(1000);
    UNITY_BEGIN();
    RUN_TEST(test_Power);
    RUN_TEST(test_Ground);
    RUN_TEST(test_WiFi);
    UNITY_END();
}

void loop() {}