#include "rra_StdTypes.h"
#include <Wire.h>
#include "Proximity_Sense.h"
#include <Arduino.h>
#include "Wire_x.h"

/**
 * Global Variables
 */

static uint8 cntr {};

void setup(void) {
    pinMode(13, INPUT);
    delay(6);   // APDS9960 requires atleast 5.7ms to enter SLEEP state after POR.
    //Prox_Sensor.Init_ProximityEngine();
    Serial.begin(9600);
    Wire.begin();
    Wire.setWireTimeout();
    Wire.beginTransmission((byte)0x39);
    Wire.write(0x80);
    Wire.write(0x01);
    Wire.endTransmission();
}

void loop(void) {
    byte p_data {};

    delay(10);
 #if 0   
    if(cntr == 0)
    {
        cntr++;
        Wire.beginTransmission((byte)0x39);
        Wire.write(0x80);
        Wire.write(CFG_9960_PEN_MASK | 0x01);
        Wire.endTransmission();
        delay(500);
    }

    Wire.beginTransmission((byte)0x39);
    Wire.write(0x9c); //0x9c : PDATA
    Wire.endTransmission();


    Wire.requestFrom(0x39, 1);
    if(Wire.available())
    {
        p_data = Wire.read();
    }
    Serial.println(p_data);
#endif
    if (cntr == 0)
    {
        cntr++;
        Wire.beginTransmission((byte)0x39);
        Wire.write(0x80);
        Wire.write(0x45);
        Wire.endTransmission();
        delay(500);

        Wire.beginTransmission((byte)0x39);
        Wire.write(0xAB);
        Wire.write(0x01);
        Wire.endTransmission();
        delay(500);
    }
    Wire.beginTransmission((byte)0x39);
    Wire.write(0x80); //0x9c : PDATA
    Wire.endTransmission();


    Wire.requestFrom(0x39, 1);
    if(Wire.available())
    {
        p_data = Wire.read();
    }
    Serial.println(p_data);
}