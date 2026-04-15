#include <TM1637Display.h>

// Segment naming convention for the display:
//
//  A    -
// F B  | |
//  G    -
// E C  | |
//  D    -

const uint8_t _fail[] = {
    SEG_A | SEG_E | SEG_F | SEG_G,                  // F
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,  // A
    SEG_B | SEG_C,                                  // |
    SEG_D | SEG_E | SEG_F,                          // L
};

const uint8_t _play[] = {
    SEG_C | SEG_E,  // ||
};

const uint8_t _stop[] = {
    SEG_C | SEG_D | SEG_E | SEG_G,  // []
};

const uint8_t _blank[] = {
    SEG_G,  // -
    SEG_G,  // -
    SEG_G,  // -
    SEG_G,  // -
};

const uint8_t _loading[] = {
    SEG_D | SEG_E | SEG_F,                          // L
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,  // A
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
};

const uint8_t _hi[] = {
    SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,  // H
    SEG_B | SEG_C,                          // |
};

const uint8_t _clear[] = {
    SEG_C | SEG_E | SEG_G,                          // n
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
    SEG_C | SEG_E | SEG_G,                          // n
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          // E
};

const uint8_t _random[] = {
    SEG_E | SEG_G,                                  // r
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,  // A
    SEG_C | SEG_E | SEG_G,                          // n
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
};

const uint8_t _randomOff[] = {
    SEG_E | SEG_G,                                  // r
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
    SEG_A | SEG_E | SEG_F | SEG_G,                  // F
    SEG_A | SEG_E | SEG_F | SEG_G,                  // F
};

class YDisplay {
   public:
    YDisplay(byte clkPin, byte dioPin) : _display(clkPin, dioPin) { _display.setBrightness(DISP_BRIGHTNESS); }

    void clear() { _display.clear(); }

    void showTrack(uint16_t track, bool isPlaying) {
        _display.setSegments(isPlaying ? _play : _stop, 1);
        _display.showNumberDec(track, false, 3, 1);
    }

    void showAlbum(uint16_t album) {
        if (album == 0) {
            _display.setSegments(_clear);
        } else {
            _display.showNumberDec(album, true, 4, 0);
        }
    }

    void showFail() { _display.setSegments(_fail); }

    void showBlank() { _display.setSegments(_blank); }

    void showLoading() { _display.setSegments(_loading); }

    void showHi() {
        _display.clear();
        _display.setSegments(_hi, 2, 1);
    }

    void showRandom(bool isRandomOn) { _display.setSegments(isRandomOn ? _random : _randomOff); }

   private:
    TM1637Display _display;
};