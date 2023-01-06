#include <ESPAsyncWebServer.h>
#include <Joystick.h>
#include <Utility.h>

const int Joystick::pinPower;
const int Joystick::pinGround;
const int Joystick::pinX;
const int Joystick::pinY;
int Joystick::motorSpeedA;
int Joystick::motorSpeedB;
bool Joystick::isRightReverse;
bool Joystick::isLeftReverse;

void Joystick::Setup()
{
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
    pinMode(pinMiddleButton, INPUT);
    pinMode(pinPower, OUTPUT);
    pinMode(pinGround, OUTPUT);
    analogWrite(pinPower, Utility::Volt2ReadVal(3.0));
    analogWrite(pinGround, LOW);
}

void Joystick::Loop()
{
    int x = analogRead(pinX) / 8 - 256;
	int y = analogRead(pinY) / 8 - 256;
	int b = digitalRead(pinMiddleButton);

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