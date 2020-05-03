#include "Player.h"

#include "Sprites.h"

void Player::construct() { 
    this->pos.set_map(ROOM_SIZE/2, ROOM_SIZE/2);
    this->last_move = {PLAYER_SPEED, 1, 0};
    this->cooldown = 0;
}

void Player::update() {
    if (this->cooldown > 0) {
        --this->cooldown;
    }
}

Move Player::move_logic(const Input & input) {
    Move mv = {
        PLAYER_SPEED,
        input.x(), 
        -1*input.y(),
    };
    if (input.x() != 0 || input.y() != 0) {
        this->last_move = mv;
    }
    return mv;
}

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

Attack Player::attack_right() {
    Attack attack;
    this->cooldown = attack.magic(
            this->pos, this->last_move, PLAYER_WIDTH, PLAYER_HEIGHT);
    return attack;
}
