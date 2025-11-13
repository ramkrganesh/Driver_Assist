#ifndef _GESTURE_SENSE_H
#define _GESTURE_SENSE_H

#include "rra_StdTypes.h"

typedef enum {
    NOTHING = 0u,
    DOWNWARD,
    UPWARD,
}gesture_t;

class Gesture {
private:
    gesture_t detection {NOTHING};
public:
    gesture_t get_gesture();
};
#endif
