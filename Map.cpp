#include "Map.h"

void Map::construct_start() {
    this->room[0] = 0xffff; // top wall
    for (byte i = 1; i < ROOM_SIZE - 1; i++) {
        this->room[i] = 0x8001;
    }
    this->room[ROOM_SIZE -1] = 0xfc3f; // door on bottom
}

void Map::construct_empty() {
    for (byte i = 0; i < ROOM_SIZE; ++i) {
        this->room[i] = 0;
    }
}

bool Map::get_tile(byte x, byte y) const {
    uint16_t mask = (uint16_t)1 << (ROOM_SIZE - x - 1);
    return mask & this->room[y];
}

void Map::set_tile(byte x, byte y, bool value) {
    uint16_t mask = (uint16_t)1 << (ROOM_SIZE - x - 1);
    if (value) {
        this->room[y] = this->room[y] | mask;
    } else {
        this->room[y] = this->room[y] & (~mask);
    }
}

void Map::render(Adafruit_SSD1306 * display, int origin_x, int origin_y) const {
    for (byte row = 0; row < ROOM_SIZE; ++row) {
        int16_t y = row * WALL_SIZE - origin_y;
        if (y < SCREEN_HEIGHT && y + WALL_SIZE > SCREEN_TOP_HEIGHT) {
            for (byte col = 0; col < ROOM_SIZE; ++col) {
                int16_t x = col * WALL_SIZE - origin_x;
                if (x < SCREEN_WIDTH && x + WALL_SIZE > 0) {
                    uint16_t mask = (uint16_t)1 << (ROOM_SIZE - col - 1);
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

byte Map::check_box(Box entity, Box * collisions) const {
    Box tiles = {
        entity.left / TILE_SIZE,
        min((int)entity.right / TILE_SIZE, ROOM_SIZE-1), 
        entity.top / TILE_SIZE,
        min((int)entity.bottom / TILE_SIZE, ROOM_SIZE-1),
    };

    byte add_index = 0;
    for (byte x = tiles.left; x <= tiles.right; ++x) {
        uint16_t mask = (uint16_t)1 << (ROOM_SIZE - x - 1);
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

bool Map::can_see(const Pos &from, const Pos &to) const {
    Map checked;
    checked.construct_empty();
    double slope = (from.pixel_y() - to.pixel_y())/(from.pixel_x() - to.pixel_x());
    double intercept = from.pixel_y() - from.pixel_x()*slope;
    
    int start = min(from.pixel_x(), to.pixel_x());
    int finish = max(from.pixel_x(), to.pixel_x());
    for (int x = start; x < finish; ++x) {
        int y = slope*x + intercept;
        int tile_x = x/TILE_SIZE;
        int tile_y = y/TILE_SIZE;
        if (!checked.get_tile(tile_x, tile_y)) {
            checked.set_tile(tile_x, tile_y, true);
            if (this->get_tile(tile_x, tile_y)) {
                return false;
            }
        }
    }
    return false;
}
