#include "Game.h"
#include "BoundingBox.h"

void Game::construct() { 
   this->room_number = 1;
   this->map.construct_start();
   this->player.construct();
}

/* Steps for a move
 * 1. Get wanted move
 * 2. Execute the move
 * 3. Roll back a little if collision
 */

void do_move(Pos * pos, Move mv) {
    pos->add(mv.speed*mv.x, mv.speed*mv.y);
}

void revert_move(Pos * pos, Move mv) {
    pos->add(-1*mv.speed*mv.x, -1*mv.speed*mv.y);
}

bool check_move(Box bounds, const Map &map, long tick) {
    Box map_collisions[MAX_TILE_COLLISIONS];
    byte collisions = map.check_box(bounds, map_collisions, tick);
    if (collisions > 0) {
        return true;
    }
    return false;
}

void Game::update(const Input &input, long tick) {
    Move mv = this->player.move_logic(input);
    if (mv.moving) { 
        Pos * pos = this->player.get_pos_pointer();
        do_move(pos, mv);
        Box bounds = create_box(pos, PLAYER_WIDTH, PLAYER_HEIGHT);
        if (check_move(bounds, this->map, tick)) {
            revert_move(pos, mv);
        }
    }
}

void Game::render(Adafruit_SSD1306 * display) {
    display->clearDisplay();

    // render bottom screen
    this->player.render(display);

    Pos center = player.get_center();
    // pixel cordinates of the screen point 0, 0 to convert to screen coridinates
    int origin_x = (int)center.pixel_x() - SCREEN_WIDTH/2;
    int origin_y = (int)center.pixel_y() - (SCREEN_HEIGHT+SCREEN_TOP_HEIGHT)/2;
    
    this->map.render(display, origin_x, origin_y); 
    
    // render top menu
    display->fillRect(0, 0, SCREEN_WIDTH, SCREEN_TOP_HEIGHT, SSD1306_BLACK);

    display->display();
}


