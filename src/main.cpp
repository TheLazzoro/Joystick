#include <Arduino.h>
//#include <ESP8266WiFi.h>

int x = 0;
int y = 0;
int b = 0; // joystick "middle" button

int motorSpeedA;
int motorSpeedB;
bool isRightReverse = false;
bool isLeftReverse = false;

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(8, INPUT);
	digitalWrite(8, HIGH);
}

void loop()
{
	x = analogRead(A0) / 2 - 256;
	y = analogRead(A1) / 2 - 256;
	b = digitalRead(9);
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

	// Right steering correction
	if (motorSpeedA < 0)
		motorSpeedA = 0;
	else if (motorSpeedA > 255)
		motorSpeedA = 255;
	// Left steering correction
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