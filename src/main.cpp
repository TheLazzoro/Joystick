//#include <Arduino.h>
#include <wifi_functionality.h>
#include <WiFiManager.h>

int x = 0;
int y = 0;
int b = 0; // joystick "middle" button

int inputX = 34;
int inputY = 35;

int motorSpeedA;
int motorSpeedB;
bool isRightReverse = false;
bool isLeftReverse = false;

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(inputX, INPUT);
	pinMode(inputY, INPUT);
	//digitalWrite(8, HIGH);
}

void loop()
{
	x = analogRead(inputX) / 8 - 256;
	y = analogRead(inputY) / 8 - 256;
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