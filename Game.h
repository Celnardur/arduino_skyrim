#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "Map.h"
#include "Input.h"
#include "Sprites.h"
#include "Player.h"
#include "Entity.h"
#include "Attack.h"

class Game {
public:
    void construct();
    void update(const Input &input, uint32_t tick);
    void render(Adafruit_SSD1306 * display);

private:
    byte room_number;
    Map map;
    Player player;
    Entity entity[MAX_NUM_ENTITIES];
    Attack attack[MAX_NUM_ATTACKS];
    //Loot loot[MAX_NUM_LOOT];
};

#endif
