#include "Driver_Assist.h"
#include "Proximity_Sense.h"
#include <Arduino.h>

#define DEBUG_MODE  STD_ON

/**
 * Global Variables
 */
static ProximityEngine IndicatorProximity;

void setup(void) {
#if DEBUG_MODE
    Serial.begin(9600);
    Serial.flush();
    Serial.println("Starting Debug Mode...");
#endif
    pinMode(CFG_NANO_HWPIN_9960INT, INPUT_PULLUP);
    IndicatorProximity.Activate_APDS9960();
    IndicatorProximity.Init_ProximityEngine();
}

void loop(void) {

    if(LOW == digitalRead(CFG_NANO_HWPIN_9960INT)) {
        Indicator_Position_t stalk_position = IndicatorProximity.Get_IndicatorPosition();
        #if DEBUG_MODE
        if (DIRECTION_LEFT == stalk_position) {
            Serial.println("Stalk Position: LEFT"); //LEFT
        }
        else if (DIRECTION_RIGHT == stalk_position) {
            Serial.println("Stalk Position: RIGHT"); // 
        }
        else {
            Serial.println("Stalk Position: UNKNOWN");
        }
        #endif
    }
    else {
        #if DEBUG_MODE
        Serial.println("Stalk Position: UNKNOWN");
        #endif
    }
}