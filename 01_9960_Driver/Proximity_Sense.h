#ifndef _PROXIMITY_SENSE_H_
#define _PROXIMITY_SENSE_H_

#include "rra_StdTypes.h"

typedef enum {
    NOTHING = 0u,
    DOWNWARD,
    UPWARD,
}Proximity_t;

class ProximityEngine {
private:
    Proximity_t detection {NOTHING};
public:
    void Init_ProximityEngine(void);
};
#endif
