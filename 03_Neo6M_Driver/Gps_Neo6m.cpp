#include "Gps_Neo6m.h"
#include "TinyGPSPlus.h"    // 3rd party library

static TinyGPSPlus gps_data;
/**
 * @brief This function only esablishes serial communication with Neo 6M.
 */
void GpsModule::connectGpsmodule(void){
    Serial.begin(9600);
}

double GpsModule::getSpeed(void) {
    while(Serial.available() > 0)
    {
        gps_data.encode(Serial.read());
    }

    return gps_data.speed.kmph();
}