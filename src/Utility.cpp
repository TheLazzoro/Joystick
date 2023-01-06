#include <Utility.h>

int Utility::Volt2ReadVal(float volt)
{
    if (volt > 5)
        volt = 5;

    return volt * 204;
}