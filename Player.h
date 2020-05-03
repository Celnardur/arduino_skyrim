#ifndef PLAYER_H
#define PLAYER_H


#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pos.h"
#include "Constants.h"
#include "Input.h"
#include "Move.h"
#include "Attack.h"

class Player {
public:
    void construct();
    void update();
    void render(Adafruit_SSD1306 * display) const;

    Move move_logic(const Input & input);
    Attack attack_right();

    Pos get_pos() const { return this->pos; };
    Pos * get_pos_pointer() { return &this->pos; };
    Pos get_center() const;

    bool attack_ready() const { return this->cooldown == 0; };
private:
    Pos pos;
    Move last_move;
    byte cooldown;
};

#endif
