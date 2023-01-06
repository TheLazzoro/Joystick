#include <ESPAsyncWebServer.h>

class WiFi_Helper
{
public:
    static const char *ssid;
    static const char *pass;

    static void Setup();
    static String SerializeJoystickInput();
    static void Response_GetJoystickInput(AsyncWebServerRequest *request);
};