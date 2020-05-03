#include "Attack.h"

void Attack::update() {
    this->at.add_move(this->mv);
    if (this->time() != 0x0F) {
        ++this->duration;
    }
}

void Attack::render(Adafruit_SSD1306 * display, int origin_x, int origin_y) {
    int x = this->at.pixel_x() - origin_x;
    int y = this->at.pixel_y() - origin_y;
    
    if (x > 0-this->width() && x < SCREEN_WIDTH && 
        y > SCREEN_TOP_HEIGHT-this->height() && y < SCREEN_HEIGHT) {
        display->fillRect(x, y, this->width(), this->height(), SSD1306_WHITE);
    }
}


byte Attack::magic(Pos pos, Move mv, byte width, byte height) {
    this->at = pos;
    float max = max(abs(mv.x), abs(mv.y));
    this->at.add_pixel((mv.x/max) * width, (mv.y/max) * height);
    this->dimensions = MAGIC_DIMENSIONS;
    this->mv = mv;
    this->mv.speed = MAGIC_SPEED;
    this->duration = MAGIC_DURATION;
    this->dmg = MAGIC_DAMAGE;
    return MAGIC_COOLDOWN;
}
