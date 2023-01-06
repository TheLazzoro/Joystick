#include <WiFi_Helper.h>
#include <Joystick.h>

const char *WiFi_Helper::ssid = "Car-Access-Point";
const char *WiFi_Helper::pass = "car";
AsyncWebServer server(80);

String WiFi_Helper::SerializeJoystickInput()
{
    return String(
        String(Joystick::motorSpeedA) + ":" +
        String(Joystick::motorSpeedB) + ":" +
        String(Joystick::isRightReverse) + ":" +
        String(Joystick::isLeftReverse));
}

void WiFi_Helper::Response_GetJoystickInput(AsyncWebServerRequest *request)
{
    request->send_P(200, "text/html", SerializeJoystickInput().c_str());
}

void WiFi_Helper::Setup()
{
    Serial.println("Access point setup...");
	WiFi.mode(WIFI_STA);
	WiFi.softAP(ssid);
	// For some reason the network does not show up when setting a password.
	// WiFi.softAP(ssid, pass);

	IPAddress IP = WiFi.softAPIP();
	Serial.print("IP: ");
	Serial.println(IP);

	server.on("/joystick", HTTP_GET, WiFi_Helper::Response_GetJoystickInput);
	server.begin();
	Serial.println("Server started.");

	delay(3000);
}