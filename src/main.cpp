//#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>


int x = 0;
int y = 0;
int b = 0; // joystick "middle" button

int inputX = 34;
int inputY = 35;
int inputMiddleButton = 32;

int motorSpeedA;
int motorSpeedB;
bool isRightReverse = false;
bool isLeftReverse = false;

const char *ssid = "Car-Access-Point";
const char *pass = "car";
AsyncWebServer server(80);
const char *PARAM_MESSAGE = "message";

void responseGetJoystickInput(AsyncWebServerRequest *request);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(inputX, INPUT);
	pinMode(inputY, INPUT);
	pinMode(inputMiddleButton, INPUT);

	Serial.println("Access point setup...");
	WiFi.mode(WIFI_STA);
	WiFi.softAP(ssid);
	// For some reason the network does not show up when setting a password.
	// WiFi.softAP(ssid, pass);

	IPAddress IP = WiFi.softAPIP();
	Serial.print("IP: ");
	Serial.println(IP);

	server.on("/joystick", HTTP_GET, responseGetJoystickInput);
	server.begin();
	Serial.println("Server started.");

	delay(3000);
}

String readJoystickInput()
{
	return String(
		String(motorSpeedA) + ":" +
		String(motorSpeedB) + ":" +
		String(isRightReverse) + ":" +
		String(isLeftReverse)
		);
}

void responseGetJoystickInput(AsyncWebServerRequest *request)
{
	request->send_P(200, "text/html", readJoystickInput().c_str());
}


void loop()
{
	x = analogRead(inputX) / 8 - 256;
	y = analogRead(inputY) / 8 - 256;
	b = digitalRead(inputMiddleButton);
	Serial.print("\n");

	// initial forward/backwards movement
	motorSpeedA = x;
	motorSpeedB = x;

	// reverse movement check
	isRightReverse = motorSpeedA > 0;
	isLeftReverse = motorSpeedB > 0;
	if (isRightReverse)
		motorSpeedA *= -1;
	if (isLeftReverse)
		motorSpeedB *= -1;

	// TODO: Remove this hacky fix
	motorSpeedA *= -1;
	motorSpeedB *= -1;

	// Steering
	if (y < 0)
		motorSpeedA -= y;
	else
		motorSpeedB += y;

	// Right steering
	if (motorSpeedA < 0)
		motorSpeedA = 0;
	else if (motorSpeedA > 255)
		motorSpeedA = 255;
	// Left steering
	if (motorSpeedB < 0)
		motorSpeedB = 0;
	else if (motorSpeedB > 255)
		motorSpeedB = 255;

	Serial.print("A Speed: " + String(motorSpeedA) +
				 "     B Speed: " + String(motorSpeedB) +
				 "     revA: " + String(isRightReverse) +
				 "     revB: " + String(isLeftReverse) +
				 "     turn: " + String(y));

	delay(10);
}