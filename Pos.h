#ifndef POS_H
#define POS_H

#include <Arduino.h>
#include "Constants.h"

class Pos {

    Pos() : x(0), y(0), xsub(0), ysub(0) {}
    Pos(byte x, byte y) : x(x), y(y), xsub(0), ysub(0) {}

    void set_map(byte x, byte y) {
        this->x = x*
    }

    void add(int32_t x, int32_t y) {
        int32_t x_total = ((int32_t)this->x * BYTE_SIZE + (int32_t)this->xsub) + x;
        this->x = x_total / BYTE_SIZE;
        this->xsub = x_total % BYTE_SIZE;

        int32_t y_total = ((int32_t)this->y * BYTE_SIZE + (int32_t)this->ysub) + y;
        this->y = y_total / BYTE_SIZE;
        this->ysub = y_total % BYTE_SIZE;
    }

private:
    // for keeping track of partial pixel cordinates
    byte x;
    byte y;
    byte xsub;
    byte ysub;
};

#define print_pos(pos) Serial.println("X: " + String((pos).x) + ", Y: " + String((pos).y));

#endif
