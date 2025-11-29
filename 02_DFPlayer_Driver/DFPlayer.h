#ifndef _DFPLAYER_H_
#define _DFPLAYER_H_

#include "Std_Types.h"
#include "Global_Cfg.h"

typedef enum {
    DFPLAYER_IDLE,
    DFPLAYER_BUSY,
} DFPStatusType;

class DFPlayer {
private:
    DFPStatusType DFPStatus;

public:
    void setVolume(uint8);
    DFPStatusType getStatus(void);
    void playTrack(byte);

    DFPlayer();
};

#endif //_DFPLAYER_H_