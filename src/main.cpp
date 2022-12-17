// #include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

int x = 0;
int y = 0;
int b = 0; // joystick "middle" button

int pinPower = 27;
int pinGround = 26;
int pinX = 34;
int pinY = 35;
int pinMiddleButton = 32;

int motorSpeedA;
int motorSpeedB;
bool isRightReverse = false;
bool isLeftReverse = false;

const char *ssid = "Car-Access-Point";
const char *pass = "car";
AsyncWebServer server(80);
const char *PARAM_MESSAGE = "message";

void responseGetJoystickInput(AsyncWebServerRequest *request);
int Volt2ReadVal(float volt);

void setup()
{
	Serial.begin(115200);
	pinMode(pinX, INPUT);
	pinMode(pinY, INPUT);
	pinMode(pinMiddleButton, INPUT);
	pinMode(pinPower, OUTPUT);
	pinMode(pinGround, OUTPUT);
	analogWrite(pinPower, Volt2ReadVal(3.0));
	analogWrite(pinGround, LOW);

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
		String(isLeftReverse));
}

void responseGetJoystickInput(AsyncWebServerRequest *request)
{
	request->send_P(200, "text/html", readJoystickInput().c_str());
}

int Volt2ReadVal(float volt)
{
	if(volt > 5)
		volt = 5;
		
	return volt * 204;
}

void loop()
{
	x = analogRead(pinX) / 8 - 256;
	y = analogRead(pinY) / 8 - 256;
	b = digitalRead(pinMiddleButton);

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

	//Serial.println("x: " + String(analogRead(pinX)) + "   y: " + String(analogRead(pinY)));

	Serial.println("A Speed: " + String(motorSpeedA) +
				 "     B Speed: " + String(motorSpeedB) +
				 "     revA: " + String(isRightReverse) +
				 "     revB: " + String(isLeftReverse) +
				 "     turn: " + String(y));

	delay(10);
}