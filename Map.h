#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pos.h"
#include "Constants.h"
#include "BoundingBox.h"
#include "Move.h"

class Map {
public:
    void construct_start();
    void construct_empty();
    void render(Adafruit_SSD1306 * display, int origin_x, int origin_y) const;

    bool get_tile(byte x, byte y) const;
    void set_tile(byte x, byte y, bool value);

    byte check_box(Box box, Box * collisions) const;
    bool can_see(const Pos &from, const Pos &to) const;
private:
    uint16_t room[ROOM_SIZE];
};

#endif
