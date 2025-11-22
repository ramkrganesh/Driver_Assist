#include "Driver_Assist.h"
#include "Proximity_Sense.h"
#include <Arduino.h>

#define DEBUG_MODE  STD_ON

/**
 * Global Variables
 */

 void setup(void) {
#if DEBUG_MODE
    Serial.begin(9600);
    Serial.flush();
    Serial.println("Starting Debug Mode...");
#endif
    pinMode(CFG_NANO_HWPIN_9960INT, INPUT);
    static ProximityEngine IndicatorProximity;
    IndicatorProximity.Init_ProximityEngine();
    IndicatorProximity.Start_ProximityEngine();
}

void loop(void) {
    if(LOW == digitalRead(CFG_NANO_HWPIN_9960INT)) {
    }
}