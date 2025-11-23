#include "Proximity_Sense.h"
#include "Arduino.h"
#include "Wire.h"


/**
 * @brief Friend function to ProximityEngine.
 * This is a helper function to send I2C command to APDS9960
 */
void Send_Cmd_9960(const uint8 reg, const uint8 val) {
    Wire.begin();
    Wire.beginTransmission((uint8)CFG_9960_I2C_ADDR);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
    Wire.end();
    delay(1);
}

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
    delay(6);   // allow APDS to enter sleep after POR.

    Send_Cmd_9960(REG_9960_PILT, CFG_9960_PILT);
    Send_Cmd_9960(REG_9960_PIHT, CFG_9960_PIHT);
    Send_Cmd_9960(REG_9960_PERS, CFG_9960_PPERS);
    Send_Cmd_9960(REG_9960_PPULSE, CFG_9960_PPLEN | CFG_9960_PPULSE);
    Send_Cmd_9960(REG_9960_CONTROL, CFG_9960_LDRIVE | CFG_9960_PGAIN);
    Send_Cmd_9960(REG_9960_CONFIG2, CFG_9960_PSIEN | CFG_9960_LEDBOOST);
    Send_Cmd_9960(REG_9960_CONFIG3, CFG_9960_PCMP | CFG_9960_SAI);
    Send_Cmd_9960(REG_9960_WTIME, CFG_9960_WTIME);
    Send_Cmd_9960(REG_9960_CONFIG1, CFG_9960_WLONG);
    Send_Cmd_9960(REG_9960_ENABLE, CFG_9960_PIEN_EN | CFG_9960_WEN_EN | CFG_9960_PEN_EN | CFG_9960_PON_EN);

    delay(7);   // allow APDS to exit sleep after enabling proximity engine.
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
