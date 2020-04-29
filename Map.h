#ifndef MAP_H
#define MAP_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pos.h"
#include "Constants.h"

class Map {
public:
    void construct_start();
    void render(Adafruit_SSD1306 * display, Pos center);
private:
    uint32_t room[ROOM_SIZE];
};

#endif
