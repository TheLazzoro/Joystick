//#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

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
const char *pass = "?";
const char* serverNameSpeed = "http://192.168.4.1/speed";
const char* serverNameTest = "http://192.168.4.1/test";

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(inputX, INPUT);
	pinMode(inputY, INPUT);
	pinMode(inputMiddleButton, INPUT);

	// connecting -> disconnecting -> reconnecting makes it work for whatever reason.
	WiFi.begin(ssid);
	delay(1000);
	WiFi.disconnect();
	delay(1000);
	WiFi.begin(ssid);

	Serial.print("Connecting");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to Wifi network: ");
	Serial.println(ssid);
	Serial.print("Local IP: ");
	Serial.println(WiFi.localIP());

	delay(3000);
}

int count = 0;
void loop()
{
	if (WiFi.status() == WL_CONNECTED)
	{
		HTTPClient httpSpeed;
		HTTPClient httpTest;
		httpSpeed.begin(serverNameSpeed);
		httpTest.begin(serverNameTest);
		httpSpeed.addHeader("Content-Type", "text/plain");
		String postData = "1:2:3:4";
		Serial.print("Test: ");
		Serial.println(httpTest.GET());
		//Serial.println(httpSpeed.POST(postData));
		count += 1;
		Serial.println(count);
		Serial.println("");
		delay(60);
		return;
	}

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