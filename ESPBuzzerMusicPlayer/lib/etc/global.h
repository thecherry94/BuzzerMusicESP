#include <Arduino.h>


#pragma once

#define __DEBUG__

#ifdef __DEBUG__
    #define DEBUG_PRINT(x) Serial.printf(x)
    #define DEBUG_PRINTF(x, ...) Serial.printf(x, __VA_ARGS__)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTF(x, ...) 
#endif


struct MusicTone
{
    uint32_t frequency;
    double duration;
};