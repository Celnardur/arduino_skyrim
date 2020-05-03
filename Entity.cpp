#include "Entity.h"
#include "Sprites.h"

void Entity::set(byte x, byte y, byte flags) {
    this->pos.set_map(x, y);
    this->flags = flags;
}

Move Entity::ai(Pos player, const Map &map) const {
    int32_t run = (int32_t)player.get_x() - (int32_t)this->pos.get_x();
    int32_t rise = (int32_t)player.get_y() - (int32_t)this->pos.get_y();
    uint32_t divisor = max(abs(rise), abs(run));
    Move mv = {
        MONSTER_SPEED,
        (float)run / divisor,
        (float)rise / divisor,
    };
    return mv;
}

void Entity::render(Adafruit_SSD1306 * display, int origin_x, int origin_y) {
    int x = this->pos.pixel_x() - origin_x;
    int y = this->pos.pixel_y() - origin_y;
    
    if (x > 0-MONSTER_WIDTH && x < SCREEN_WIDTH && 
        y > SCREEN_TOP_HEIGHT-MONSTER_HEIGHT && y < SCREEN_HEIGHT) {
        display->drawBitmap(x, y, normal_monster, 
                MONSTER_WIDTH, MONSTER_HEIGHT, 1); 
    }
}
