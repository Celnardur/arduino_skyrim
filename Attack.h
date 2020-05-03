#ifndef ATTACK_H
#define ATTACK_H

#include "Pos.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define WIDTH_MASK 0x0F
#define HEIGHT_MASK 0xF0
#define HEIGHT_SHIFT 4

#define TIME_MASK 0x0F
#define EXPIRES_MASK 0xF0
#define EXPIRES_SHIFT 4

class Attack {
public:
    void update(); 
    void render(Adafruit_SSD1306 * display, int origin_x, int origin_y);

    byte magic(Pos pos, Move mv, byte width, byte height);

    byte width() const { return this->dimensions & WIDTH_MASK; };
    byte height() const { return (this->dimensions & HEIGHT_MASK) >> HEIGHT_SHIFT; };
    byte time() const { return this->duration & TIME_MASK; };
    byte expires() const { return (this->duration & EXPIRES_MASK) >> EXPIRES_SHIFT; };
    bool done() const { return this->time() > this->expires(); };
    byte damage() const { return this->dmg; };

    void make_done() { this->duration = 0x0F; };
private:
    Pos at;
    byte dimensions;
    Move mv;
    byte duration;
    byte dmg;
};



#endif
