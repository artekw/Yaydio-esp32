#pragma once

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

enum YRotaryEncoderDirection { CCW, NONE, CW };

class YRotaryEncoder {
   public:
    YRotaryEncoder(byte clkPin, byte dtPin) : _encoder(clkPin, dtPin) {}

    void loop() {
        long newPos = _encoder.read();
        long delta = newPos - _lastPos;

        if (delta >= _stepsPerClick) {
            _direction = CW;
            _lastPos = newPos;
        } else if (delta <= -_stepsPerClick) {
            _direction = CCW;
            _lastPos = newPos;
        } else {
            _direction = NONE;
        }
    }

    bool justTurnedCW()  { return _direction == CW; }
    bool justTurnedCCW() { return _direction == CCW; }
    YRotaryEncoderDirection getDirection() { return _direction; }

   private:
    Encoder _encoder;
    long _lastPos = 0;
    const int _stepsPerClick = 4;  // typowy enkoder mechaniczny = 4 impulsy na klik
    YRotaryEncoderDirection _direction = NONE;
};