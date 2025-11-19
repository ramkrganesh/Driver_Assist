#ifndef _PROXIMITY_SENSE_H_
#define _PROXIMITY_SENSE_H_

#include "rra_StdTypes.h"
#include "Proximity_Cfg.h"

/**
 * Macros:
 */


typedef enum {
    NOTHING = 0u,
    DOWNWARD,
    UPWARD,
}Proximity_t;

class ProximityEngine {
private:
    Proximity_t detection;

public:
    ProximityEngine();
    void Init_ProximityEngine(void);
};
#endif
