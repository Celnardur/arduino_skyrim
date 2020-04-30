#include "Map.h"

void Map::construct_start() {
    this->room[0] = 0xfffe7fff; // top wall
    for (byte i = 1; i < ROOM_SIZE - 1; i++) {
        if (i % 3 == 0) {
            this->room[i] = 0x88880889;
        } else {
            this->room[i] = 0x80000001;
        }
    }
    this->room[ROOM_SIZE/2] = 0x00000000; // door on left
    this->room[ROOM_SIZE -1] = 0xfffe7fff; // door on bottom
}

void Map::render(Adafruit_SSD1306 * display, int origin_x, int origin_y) const {
    for (byte row = 0; row < ROOM_SIZE; ++row) {
        int16_t y = row * WALL_SIZE - origin_y;
        if (y < SCREEN_HEIGHT && y + WALL_SIZE > SCREEN_TOP_HEIGHT) {
            for (byte col = 0; col < ROOM_SIZE; ++col) {
                int16_t x = col * WALL_SIZE - origin_x;
                if (x < SCREEN_WIDTH && x + WALL_SIZE > 0) {
                    uint32_t mask = (uint32_t)1 << (ROOM_SIZE - col - 1);
                    if (mask & this->room[row]) {
                        display->fillRect(
                            x, y, 
                            WALL_SIZE, WALL_SIZE, 
                            SSD1306_WHITE
                        );
                    }
                }
            }
        }
    }
}

byte Map::check_box(Box entity, Box * collisions, long tick) const {
    Box tiles = {
        entity.left / TILE_SIZE,
        min((int)entity.right / TILE_SIZE, ROOM_SIZE-1), 
        entity.top / TILE_SIZE,
        min((int)entity.bottom / TILE_SIZE, ROOM_SIZE-1),
    };

    byte add_index = 0;
    for (byte x = tiles.left; x <= tiles.right; ++x) {
        uint32_t mask = (uint32_t)1 << (ROOM_SIZE - x - 1);
        for (byte y = tiles.top; y <= tiles.bottom; ++y) {
            if (mask & this->room[y]) {
                collisions[add_index] = {
                    x*TILE_SIZE,
                    (x+1)*TILE_SIZE,
                    y*TILE_SIZE,
                    (y+1)*TILE_SIZE
                };
                add_index++;
            }
        }
    }

    return add_index;
}
