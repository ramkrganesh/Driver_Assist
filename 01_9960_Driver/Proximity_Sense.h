#ifndef _PROXIMITY_SENSE_H_
#define _PROXIMITY_SENSE_H_

#include "Std_Types.h"
#include "Global_Cfg.h"
#include "Reg_9960.h"

//- --------------------------------------------------------------------------------------------------------------------
/**
 * Typedefs
 */
typedef enum {
    DIRECTION_DEFAULT = 0u,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
}Indicator_Position_t;

/**
 * @name : ProximityEngine
 * @brief: Handles the "proximity engine" in APDS-9960 module.
 */
class ProximityEngine {
private:
    Indicator_Position_t indicator_pos;

public:
    ProximityEngine();
    void Init_ProximityEngine(void);
    void Activate_APDS9960(void);
    Indicator_Position_t Get_IndicatorPosition(void);
};
#endif
