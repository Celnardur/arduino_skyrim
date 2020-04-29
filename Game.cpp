#include "Game.h"

void Game::construct() { 
   this->room_number = 1;
   this->map.construct_start();
   this->player.construct(ROOM_HEIGHT, ROOM_WIDTH);
}

void Game::update(const Input &input, long tick) {
    this->player.move(input);
}

void Game::render(Adafruit_SSD1306 * display) {
    display->clearDisplay();
    this->map.render(display, player.get_center()); 
    this->player.render(display);
    display->fillRect(0, 0, SCREEN_WIDTH, SCREEN_TOP_HEIGHT, SSD1306_BLACK);
    display->display();
}


