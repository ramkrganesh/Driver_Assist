#include <Arduino.h>
#include "Driver_Assist.h"
#include "Proximity_Sense.h"
#include "DFPlayer.h"
#include "Gps_Neo6m.h"

#define DEBUG_MODE false
static const double SPEED_MAX_KMH = 60.0;
static const double SPEED_WARN_LOWER_KMH = 10.0;
static const double SPEED_WARN_UPPER_KMH = 35.0;
static const unsigned long STARTUP_DELAY_MS = 3000ul;
static const unsigned long LOOP_DELAY_MS = 100ul;

static ProximityEngine IndicatorProximity;
static DFPlayer DFPlayerModule;
static GpsModule GpsData;
static bool warnRightBeforeLeftPlayed = false;

static void initHardware();
static void processSpeedWarnings(double speed);
static void processIndicator();

void setup(void) {
    delay(STARTUP_DELAY_MS); // allow DFPlayer to initialize

    if (DEBUG_MODE) {
        Serial.begin(9600);
        Serial.flush();
        Serial.println(F("Starting Debug Mode..."));
    }

    initHardware();
}

void loop(void) {
    double speed = GpsData.getSpeed();
    processSpeedWarnings(speed);
    processIndicator();

    delay(LOOP_DELAY_MS);
}

static void initHardware() {
    pinMode(CFG_NANO_HWPIN_9960INT, INPUT_PULLUP);
    IndicatorProximity.Activate_APDS9960();

    pinMode(CFG_NANO_HWPIN_DFP_RX, INPUT);
    pinMode(CFG_NANO_HWPIN_DFP_TX, OUTPUT);
    pinMode(CFG_NANO_HWPIN_DFP_BUSY, INPUT);
    DFPlayerModule.init();

    if (DEBUG_MODE == false) {
        GpsData.connectGpsmodule();
    }
}

static void processSpeedWarnings(double speed) {
    if (speed > SPEED_MAX_KMH) {
        return;
    }

    if (speed > SPEED_WARN_LOWER_KMH && speed < SPEED_WARN_UPPER_KMH) {
        if (!warnRightBeforeLeftPlayed) {
            DFPlayerModule.playTrack(TRACK_RIGHT_BEFORE_LEFT);
            warnRightBeforeLeftPlayed = true;
        }
    } else if (speed > SPEED_WARN_UPPER_KMH) {
        warnRightBeforeLeftPlayed = false;
    }
}

static void processIndicator() {
    if (digitalRead(CFG_NANO_HWPIN_9960INT) != LOW) {
#if DEBUG_MODE
        Serial.println(F("Stalk Position: UNKNOWN"));
#endif
        return;
    }

    const Indicator_Position_t stalk_position = IndicatorProximity.Get_IndicatorPosition();

    if (stalk_position == DIRECTION_LEFT) {
#if DEBUG_MODE
        Serial.println(F("Stalk Position: LEFT"));
#endif
        DFPlayerModule.playTrack(TRACK_LEFT_ONCOMING);
    } else if (stalk_position == DIRECTION_RIGHT) {
#if DEBUG_MODE
        Serial.println(F("Stalk Position: RIGHT"));
#endif
        DFPlayerModule.playTrack(TRACK_RIGHT);
    } else {
#if DEBUG_MODE
        Serial.println(F("Stalk Position: UNKNOWN"));
#endif
    }
}
