#ifndef PLAYER_H
#define PLAYER_H


#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pos.h"
#include "Constants.h"
#include "Input.h"

class Player {
public:
    void construct(uint16_t room_height, uint16_t room_width);
    void render(Adafruit_SSD1306 * display) const;

    void move(const Input & input);

    Pos get_pos() const { return this->pos; };
    Pos get_center() const { 
        Pos pos(this->pos.x + PLAYER_WIDTH/2, this->pos.y - PLAYER_HEIGHT/2);
        return pos;
    };
private:
    Pos pos;
};

#endif
