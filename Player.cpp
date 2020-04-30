#include "Player.h"

#include "Sprites.h"

void Player::construct() { 
    this->pos.set_map(ROOM_SIZE/2, ROOM_SIZE/2);
}

Move Player::move_logic(const Input & input) {
    return {
        PLAYER_SPEED,
        input.x(), 
        -1*input.y(),
        true
    };
}

/*
void Player::move(const Input & input) {
    int32_t speed = 1024;
    int32_t x_move = speed * input.x();
    int32_t y_move =-1 * speed * input.y();
    this->pos.add(x_move, y_move);
    this->pos.print();
}
*/

void Player::render(Adafruit_SSD1306 * display) const {
    display->drawBitmap(
        (display->width()  - DOVAHKIIN_WIDTH ) / 2,
        (display->height() - DOVAHKIIN_HEIGHT + SCREEN_TOP_HEIGHT) / 2,
        dovahkiin, DOVAHKIIN_WIDTH, DOVAHKIIN_HEIGHT, 1
    );
}

Pos Player::get_center() const {
    Pos center = this->pos;
    center.add_pixel(PLAYER_WIDTH/2, PLAYER_HEIGHT/2);
    return center;
}
