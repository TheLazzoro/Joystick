//#include <Arduino.h>
#include <wifi_functionality.h>
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

const char wifi_name[] = "WiFimodem-9846";
const char wifi_pass[] = "jwmymdz4yw";
WiFiManager wifiManager;

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(inputX, INPUT);
	pinMode(inputY, INPUT);
	pinMode(inputMiddleButton, INPUT);

	WiFi.mode(WIFI_STA);
	bool connected = WiFi.softAP(wifi_name, wifi_pass);
	Serial.println(String(connected));
	delay(3000);
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