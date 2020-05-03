#include "Game.h"
#include "BoundingBox.h"

void Game::construct() { 
    this->room_number = 1;
    this->map.construct_start();
    this->player.construct();
    for (int i = 0; i < MAX_NUM_ENTITIES; ++i) {
        this->entity[i].make_empty();
    }
    this->entity[0].set(10, 10, 0x10);
    for (byte i = 0; i < MAX_NUM_ATTACKS; ++i) {
        this->attack[i].make_done();
    }
}

/* Steps for a move
 * 1. Get wanted move
 * 2. Execute the move
 * 3. Roll back a little if collision
 */

void do_move(Pos * pos, Move mv) {
    pos->add_move(mv);
}

void revert_move(Pos * pos, Move mv) {
    pos->add(-1*mv.speed*mv.x, -1*mv.speed*mv.y);
}

bool check_move(Box bounds, const Map &map) {
    Box map_collisions[MAX_TILE_COLLISIONS];
    byte collisions = map.check_box(bounds, map_collisions);
    if (collisions > 0) {
        return true;
    }
    return false;
}

void move_system(Pos * pos, Move mv, byte width, byte height, const Map &map) {
    if (mv.speed != 0) { 
        do_move(pos, mv);
        Box bounds = create_box(pos, width, height);
        if (check_move(bounds, map)) {
            revert_move(pos, mv);
        }
    }
}

void Game::update(const Input &input, uint32_t tick) {
    this->player.update();
    Move mv = this->player.move_logic(input);
    move_system(this->player.get_pos_pointer(), mv, 
            PLAYER_WIDTH, PLAYER_HEIGHT, 
            this->map);
    
    // move monsters
    for (int i = 0; i < MAX_NUM_ENTITIES; ++i) {
        if (this->entity[i].was_created() && !this->entity[i].is_dead()) {
            mv = this->entity[i].ai(this->player.get_pos(), this->map);
            move_system(this->entity[i].get_pos_pointer(), mv,
                    this->entity[i].get_width(), 
                    this->entity[i].get_height(),
                    this->map);
        }
    }

    // move attacks
    for (byte i = 0; i < MAX_NUM_ATTACKS; ++i) {
        if (!this->attack[i].done()) {
            this->attack[i].update();
        }
    }

    // insert new attack
    if (input.right() && this->player.attack_ready()) { 
        Serial.println("Ready to insert new attack");
        Attack new_attack = this->player.attack_right();
        // insert into attack array 
        Serial.println(this->attack[0].time());
        Serial.println(this->attack[0].expires());
        for (byte i = 0; i < MAX_NUM_ATTACKS; ++i) {
            if (this->attack[i].done()) {
                Serial.println("Inserting attack");
                this->attack[i] = new_attack;
                break;
            }
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

    // render entities
    for (byte i = 0; i < MAX_NUM_ENTITIES; ++i) {
        if (this->entity[i].was_created() && !this->entity[i].is_dead()) {
            this->entity[i].render(display, origin_x, origin_y);
        }
    }

    for(byte i = 0; i < MAX_NUM_ATTACKS; ++i) {
        if (!this->attack[i].done()) {
            this->attack[i].render(display, origin_x, origin_y);
        }
    }

    // render top menu
    display->fillRect(0, 0, SCREEN_WIDTH, SCREEN_TOP_HEIGHT, SSD1306_BLACK);

    display->display();
}


