#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pos.h"
#include "Constants.h"
#include "BoundingBox.h"

class Map {
public:
    void construct_start();
    void render(Adafruit_SSD1306 * display, int origin_x, int origin_y) const;

    byte check_box(Box box, Box * collisions, long tick) const;
private:
    uint32_t room[ROOM_SIZE];
};

#endif
