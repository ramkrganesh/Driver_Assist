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
    delay(6);   // Wait for atleast 6ms for POR to Initialization of 9960
    Wire.begin();
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_ENABLE);                 // (1)
    Wire.write(CFG_9960_PIEN_EN | CFG_9960_PON_EN);

    Wire.write(REG_9960_PILT);                   // (2)
    Wire.write(CFG_9960_PILT);

    Wire.write(REG_9960_PIHT);                   // (3)
    Wire.write(CFG_9960_PIHT);

    Wire.write(REG_9960_PERS);                   // (4)
    Wire.write(CFG_9960_PPERS);

    Wire.write(REG_9960_PPULSE);                 // (5)
    Wire.write(CFG_9960_PPLEN | CFG_9960_PPULSE);

    Wire.write(REG_9960_CONTROL);                 // (6)
    Wire.write(CFG_9960_LDRIVE | CFG_9960_PGAIN);

    Wire.write(REG_9960_CONFIG2);                 // (7)
    Wire.write(CFG_9960_PSIEN | CFG_9960_LEDBOOST);

    Wire.write(REG_9960_CONFIG3);                 // (8)
    Wire.write(CFG_9960_PCMP | CFG_9960_SAI);
    
    Wire.endTransmission();
    Wire.end();
}


/**
 * @brief : This function "starts" proximity detection engine in APDS9960
 */
void ProximityEngine::Start_ProximityEngine(void){
    Wire.begin();
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_ENABLE);
    Wire.write(CFG_9960_PIEN_EN | CFG_9960_PEN_EN | CFG_9960_PON_EN);
    Wire.endTransmission();
    Wire.end();
    delay(7); // wait atleast 7ms to EXIT SLEEP
}

/**
 * @brief : This function returns the position of Indicator.
 * The PDATA register of 9960 is read and the value is checked to find the
 * position of indicator stalk.
 * This function also clears the Interrupt flag. (PICLEAR)
 */
Indicator_Position_t ProximityEngine::Get_IndicatorPosition(void) {
    Indicator_Position_t position {DIRECTION_DEFAULT};
    uint8 proximity_reading {};

    Wire.begin();
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_PDATA);
    Wire.endTransmission();

    Wire.requestFrom((uint8)CFG_9960_I2C_ADDR, 1);
    if(Wire.available()) {
        proximity_reading = Wire.read();
    }

    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_PDATA);
    Wire.write((uint8)0x00);    // Any value can be written to clear the interrupt
    Wire.endTransmission();
    Wire.end();

    if (proximity_reading < CFG_9960_PILT) {
        position = DIRECTION_LEFT;
    }
    else if (proximity_reading > CFG_9960_PIHT){
        position = DIRECTION_RIGHT;
    }
    return position;
}
