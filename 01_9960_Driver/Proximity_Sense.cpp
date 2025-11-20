#include "Proximity_Sense.h"
#include "Arduino.h"
#include "Wire.h"


/**
 * @brief Class Constructor
 */
ProximityEngine::ProximityEngine()
: indicator_pos {DIRECTION_DEFAULT} {
    // Nothing more to do !
}


/**
 * @brief : Initialization member function. This function only initializes the
 *          Proximity-Engine of APDS9960. This function does NOT automatically
 *          start the proximity detection.
 */
void ProximityEngine::Init_ProximityEngine(void){
    Wire.begin();
    Wire.setWireTimeout();
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_ENABLE);                 // (1)
    Wire.write(CFG_9960_PIEN_EN | CFG_9960_PON_EN);

    Wire.write(REG_PILT);                   // (2)
    Wire.write(CFG_9960_PILT);

    Wire.write(REG_PIHT);                   // (3)
    Wire.write(CFG_9960_PIHT);

    Wire.write(REG_PERS);                   // (4)
    Wire.write(CFG_9960_PPERS);

    Wire.write(REG_PPULSE);                 // (5)
    Wire.write(CFG_9960_PPLEN | CFG_9960_PPULSE);
    Wire.endTransmission();
}


/**
 * @brief : This function "starts" proximity detection engine in APDS9960
 */
void ProximityEngine::Start_ProximityEngine(void){
    Wire.begin();
    Wire.setWireTimeout();
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_ENABLE);
    Wire.write(CFG_9960_PIEN_EN | CFG_9960_PEN_EN | CFG_9960_PON_EN);
    Wire.endTransmission();
}
