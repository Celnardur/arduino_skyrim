#include "Player.h"

#include "Sprites.h"

void Player::construct(uint16_t room_height, uint16_t room_width) { 
    this->pos.x = (room_width - PLAYER_WIDTH) / 2;
    this->pos.y = (room_height - PLAYER_HEIGHT) / 2;
}

void Player::move(const Input & input) {
    int32_t speed = 1028;
    int32_t x_move = speed * input.x();
    int32_t y_move =-1 * speed * input.y();
    this->pos.add(x_move, y_move);
}

void Player::render(Adafruit_SSD1306 * display) const {
    display->drawBitmap(
        (display->width()  - DOVAHKIIN_WIDTH ) / 2,
        (display->height() - DOVAHKIIN_HEIGHT + SCREEN_TOP_HEIGHT) / 2,
        dovahkiin, DOVAHKIIN_WIDTH, DOVAHKIIN_HEIGHT, 1
    );
}
