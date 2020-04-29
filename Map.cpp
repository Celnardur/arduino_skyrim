#include "Map.h"

void Map::construct_start() {
    this->room[0] = -1; // top wall
    for (byte i = 1; i < ROOM_SIZE - 1; i++) {
        if (i % 3 == 0) {
            this->room[i] = 0x88880889;
        } else {
            this->room[i] = 0x80000001;
        }
    }
    this->room[ROOM_SIZE -1] = 0xfffe7fff; // door on bottom
}

void Map::render(Adafruit_SSD1306 * display, Pos center) {
    int origin_x = (int)center.x - SCREEN_WIDTH/2; 
    int origin_y = (int)center.y - SCREEN_HEIGHT/2; 
    Serial.println(origin_x);

    for (byte row = 0; row < ROOM_SIZE; ++row) {
        int16_t y = row * WALL_SIZE - origin_y;
        if (y < SCREEN_HEIGHT && y + WALL_SIZE > SCREEN_TOP_HEIGHT) {
            for (byte col = 0; col < ROOM_SIZE; ++col) {
                int16_t x = col * WALL_SIZE - origin_x;
                if (x < SCREEN_WIDTH && x + WALL_SIZE > 0) {
                    uint32_t mask = (uint32_t)1 << (ROOM_SIZE - col - 1);
                    if (mask & this->room[row]) {
                        display->fillRect(x, y, WALL_SIZE, WALL_SIZE, SSD1306_WHITE);
                    }
                }
            }
        }
    }
}
