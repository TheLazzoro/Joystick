class Joystick
{
    public:
        static const int pinPower = 27;
        static const int pinGround = 26;
        static const int pinX = 34;
        static const int pinY = 35;
        static const int pinMiddleButton = 32;

        static int motorSpeedA;
        static int motorSpeedB;
        static bool isRightReverse;
        static bool isLeftReverse;

        static void Setup();
        static void Loop();
};