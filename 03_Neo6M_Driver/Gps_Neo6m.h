#ifndef _GPS_NEO6M_H_
#define _GPS_NEO6M_H_

#include "Std_Types.h"

class GpsModule {
public:
    void connectGpsmodule(void);
    double getSpeed(void);
    GpsModule() = default;
    ~GpsModule() = default;
};
#endif
