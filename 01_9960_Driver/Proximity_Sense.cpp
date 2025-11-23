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
 * @brief : This function activates proximity engine in APDS9960.
 * After activation, the proximity measurement will be made by the proximity
 * engine every 5.56ms (depends on CFG_9960_WTIME)
 */
void ProximityEngine::Activate_APDS9960(void){
    delay(6);   // allow the APDS to enter sleep after POR
    Wire.begin();

    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_PILT);                   // (3)
    Wire.write(CFG_9960_PILT);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_PIHT);                   // (4)
    Wire.write(CFG_9960_PIHT);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_PERS);                   // (5)
    Wire.write(CFG_9960_PPERS);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_PPULSE);                 // (6)
    Wire.write(CFG_9960_PPLEN | CFG_9960_PPULSE);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_CONTROL);                 // (7)
    Wire.write(CFG_9960_LDRIVE | CFG_9960_PGAIN);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_CONFIG2);                 // (8)
    Wire.write(CFG_9960_PSIEN | CFG_9960_LEDBOOST);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_CONFIG3);                 // (9)
    Wire.write(CFG_9960_PCMP | CFG_9960_SAI);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_WTIME);
    Wire.write(CFG_9960_WTIME);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_CONFIG1);
    Wire.write(CFG_9960_WLONG);
    Wire.endTransmission();
    delay(1);
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_ENABLE);
    Wire.write(CFG_9960_PIEN_EN | CFG_9960_WEN_EN | CFG_9960_PEN_EN | CFG_9960_PON_EN);
    Wire.endTransmission();
    Wire.end();
    delay(7);
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
    /* Clear Interrupt */
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_PICLEAR);
    Wire.write((uint8)0x01);    // Any value can be written to clear the interrupt
    Wire.endTransmission();

    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(REG_9960_PDATA);
    Wire.endTransmission();

    Wire.requestFrom(CFG_9960_I2C_ADDR, 1);
    if(Wire.available()) {
        proximity_reading = Wire.read();
    }
    Wire.end();

    if (proximity_reading < CFG_9960_PILT) {
        position = DIRECTION_LEFT;
    }
    else if (proximity_reading > CFG_9960_PIHT){
        position = DIRECTION_RIGHT;
    }
    return position;
}
