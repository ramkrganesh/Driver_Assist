#include "rra_StdTypes.h"
#include <Wire.h>
#include "Proximity_Sense.h"
#include <Arduino.h>

/**
 * Global Variables
 */
static ProximityEngine Prox_Sensor {};

void setup(void) {
    delay(6);   // APDS9960 requires atleast 5.7ms to enter SLEEP state after POR.
    Prox_Sensor.Init_ProximityEngine();
    Serial.begin(9600);
}

void loop(void) {
    byte p_data {};
    delay(1000);
    Wire.beginTransmission((byte)0x39);
    Wire.write(0x9c);
    Wire.endTransmission();

    Wire.requestFrom(0x39, 1);
    if(Wire.available())
    {
        p_data = Wire.read();
    }
    Serial.println(p_data);

}