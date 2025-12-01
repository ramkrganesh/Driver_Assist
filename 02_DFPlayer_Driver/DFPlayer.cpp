#include <SoftwareSerial.h>
#include "DFPlayer.h"

static uint8 txBuf[10] {0};
static SoftwareSerial DFPSerial(CFG_NANO_HWPIN_DFP_RX, CFG_NANO_HWPIN_DFP_TX);

/**
 * @brief : Perform 2's complement on tx buffer.
 */
uint16 DFPlayer::computeChecksum(const uint8* buff) {
    uint16 ret {};
    for(size_t i = 0; i < 6; i++) {
        ret += buff[i];
    }
    ret = (0xFFFF - ret) + 1;   // 2's complement
    return (ret);
}

void DFPlayer::sendCmd(DFPCmdType cmd, uint8 param) {
    uint16 checksum {};
    txBuf[0] = 0x7E;
    txBuf[1] = 0xFF;
    txBuf[2] = 0x06;
    txBuf[3] = cmd;
    txBuf[4] = 0x00;    // no feedback from DFP expected
    txBuf[5] = 0x00;    // param 1 - unused
    txBuf[6] = param;
    checksum = computeChecksum(&txBuf[1]); // checksum computed from "Version" until "Param2"
    txBuf[7] = static_cast<uint8>((checksum & 0xFF00) >> 8u);
    txBuf[8] = static_cast<uint8>(checksum & 0x00FF);
    txBuf[9] = 0xEF;
    DFPSerial.write(txBuf, 10);
    delay(100);
}

DFPlayer::DFPlayer()
: DFPStatus{DFPLAYER_IDLE} {
    // Do Nothing
}

void DFPlayer::init(void) {
    DFPSerial.begin(9600);
    sendCmd(VOL, INIT_VOLUME);
    sendCmd(TRACK, TRACK_INIT);
    delay(4000);    // wait for track to finish
}

void DFPlayer::setVolume(uint8 volLevel) {
    sendCmd(VOL, volLevel);
}

void DFPlayer::playTrack(uint8 track) {
    sendCmd(TRACK, track);
    while(getStatus() == DFPLAYER_BUSY) {
        delay(100);
    }
}

DFPStatusType DFPlayer::getStatus(void) {
    DFPStatusType ret = DFPLAYER_IDLE;
    if(digitalRead(CFG_NANO_HWPIN_DFP_BUSY) == LOW) {
        ret = DFPLAYER_BUSY;
    }
    return (ret);
}