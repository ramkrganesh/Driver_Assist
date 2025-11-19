#include "Wire_x.h"
#include <Wire.h>

void Wire_x::send_data(const i2c_protocol_t* buff, uint8 size) {
    Wire.beginTransmission((byte)CFG_9960_I2C_ADDR);
    
    for(uint8 idx {0}; idx < size; idx++) {
        Wire.write(buff[idx].addr);
        Wire.write(buff[idx].data);
    }
}