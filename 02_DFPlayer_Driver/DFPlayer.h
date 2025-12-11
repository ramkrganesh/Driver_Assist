#ifndef _DFPLAYER_H_
#define _DFPLAYER_H_

#include "Std_Types.h"
#include "Global_Cfg.h"

#define INIT_VOLUME         (0x0Fu) // Set as 15. Max possible volume 30.

enum {
    TRACK_INIT=1,
    TRACK_LEFT_ONCOMING,
    TRACK_RIGHT,
    TRACK_RIGHT_BEFORE_LEFT,
    TRACK_MAX
};


typedef enum {
    DFPLAYER_IDLE,
    DFPLAYER_BUSY,
} DFPStatusType;

typedef enum {
    TRACK   = 0x03,
    VOL     = 0x06,
}DFPCmdType;

class DFPlayer {
private:
    DFPStatusType DFPStatus;
    void sendCmd(DFPCmdType, uint8);
    uint16 computeChecksum(const uint8*);

public:
    void setVolume(uint8);
    void playTrack(byte);
    DFPStatusType getStatus(void);
    void init(void);
    void waitTrackFinish(void);

    DFPlayer();
};

#endif //_DFPLAYER_H_