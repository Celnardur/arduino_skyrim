#ifndef POS_H
#define POS_H

#include <Arduino.h>
#include "Constants.h"

#define abs(x) ((x)<0 ? -(x) : (x))
#define min(x, y) ((x)<(y) ? (x) : (y))
#define max(x, y) ((x)>(y) ? (x) : (y))

class Pos {
public:
    Pos() : x(0), y(0) {}
    Pos(byte x, byte y) : x(x), y(y) {}

    byte pixel_x() const { return this->x/PIXEL_SIZE; }
    byte pixel_y() const { return this->y/PIXEL_SIZE; }
    uint16_t get_x() const { return this->x; }
    uint16_t get_y() const { return this->y; }

    // sets the positon to that tile on the map
    inline void set_map(uint16_t x, uint16_t y) {
        this->x = x*TILE_SIZE*PIXEL_SIZE;
        this->y = y*TILE_SIZE*PIXEL_SIZE;
    }

    // sets the position to that pixel cooridinate on the map
    inline void set_pixel(uint16_t x, uint16_t y) {
        this->x = x*PIXEL_SIZE;
        this->y = y*PIXEL_SIZE;
    }

    inline void set_pixel_x(uint16_t x) { this->x = x*PIXEL_SIZE; }
    inline void set_pixel_y(uint16_t y) { this->x = x*PIXEL_SIZE; }

    // sets the postion to the given subpixel cooridinates
    void set(uint16_t x, uint16_t y) {
        this->x = x;
        this->y = y;
    }

    Pos add_pixel(int32_t x, int32_t y);

    // takes in subpixels to add to the position/
    // returns true if position is on edge. 
    Pos add(int32_t x, int32_t y);

    void print() const;

private:
    // keeps track of position in subpixel coridinates for better speed controll
    // 256 subpixels per pixel
    uint16_t x;
    uint16_t y;
};

#endif
