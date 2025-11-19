#ifndef _WIRE_X_H_
#define _WIRE_X_H_
#include "Proj_Config.h"
#include "rra_StdTypes.h"

typedef struct{
uint8 addr;
uint8 data;
}i2c_protocol_t;

class Wire_x {
private:
i2c_protocol_t i2c_buffer[CFG_I2C_BUFFER_SIZE] {};

public:
    static Wire_x& get_instance() {
        static Wire_x singleton_instance;
        return singleton_instance;
    }

    void send_data(const i2c_protocol_t*, uint8);
};
#endif
