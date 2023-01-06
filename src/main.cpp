#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <Joystick.h>
#include <WiFi_Helper.h>

void setup()
{
	Serial.begin(115200);
	Joystick::Setup();
	WiFi_Helper::Setup();
}

void loop()
{
	Joystick::Loop();
}