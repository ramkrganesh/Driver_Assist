#include "Proj_Config.h"
#include "Proximity_Sense.h"
#include "Reg_9960.h"
#include <Wire.h>

ProximityEngine::ProximityEngine()
: detection {NOTHING} {

}

void ProximityEngine::Init_ProximityEngine(void){
    Wire.begin();
    Wire.setWireTimeout();
    Wire.beginTransmission((byte)CFG_9960_I2C_ADDR);
    Wire.write(REG_ENABLE);
    Wire.write( CFG_9960_PIEN_MASK ||
                CFG_9960_PEN_MASK  ||
                CFG_9960_PON_MASK
    );
    Wire.endTransmission();
    delay(7);
}