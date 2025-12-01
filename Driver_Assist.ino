#include <Arduino.h>
#include "Driver_Assist.h"
#include "Proximity_Sense.h"
#include "DFPlayer.h"

#define DEBUG_MODE  STD_ON

/**
 * Global Variables
 */
static ProximityEngine IndicatorProximity;
static DFPlayer DFPlayerModule;

void setup(void) {
    delay(3000);    // allow DFPlayer to initialize
#if DEBUG_MODE
    Serial.begin(9600);
    Serial.flush();
    Serial.println("Starting Debug Mode...");
#endif

    /* 9960 pins */
    pinMode(CFG_NANO_HWPIN_9960INT, INPUT_PULLUP);
    IndicatorProximity.Activate_APDS9960();
    
    /* DFPlayer pins */
    pinMode(CFG_NANO_HWPIN_DFP_RX, INPUT);
    pinMode(CFG_NANO_HWPIN_DFP_TX, OUTPUT);
    pinMode(CFG_NANO_HWPIN_DFP_BUSY, INPUT);
    DFPlayerModule.init();
}

void loop(void) {

    if(LOW == digitalRead(CFG_NANO_HWPIN_9960INT)) {
        Indicator_Position_t stalk_position = IndicatorProximity.Get_IndicatorPosition();
        if (DIRECTION_LEFT == stalk_position)
        {
#if DEBUG_MODE
            Serial.println("Stalk Position: LEFT"); //LEFT
#endif
            DFPlayerModule.playTrack(TRACK_LEFT_ONCOMING);
        }
        else if (DIRECTION_RIGHT == stalk_position)
        {
#if DEBUG_MODE
            Serial.println("Stalk Position: RIGHT");
#endif
            DFPlayerModule.playTrack(TRACK_RIGHT);
        }
        else
        {
            // Ideally, This code will never be reached.
#if DEBUG_MODE
            Serial.println("Stalk Position: UNKNOWN 1");
#endif
        }

    }
    else
    {
#if DEBUG_MODE
        Serial.println("Stalk Position: UNKNOWN 2");
#endif
    }
    delay(100);
}