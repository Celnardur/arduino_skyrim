#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "Map.h"
#include "Input.h"
#include "Sprites.h"
#include "Player.h"

class Game {
public:
    void construct();
    void update(const Input &input, long tick);
    void render(Adafruit_SSD1306 * display);

private:
    byte room_number;
    Map map;
    Player player;
    //Entity entity[];
    //Attack attacks[];
    //Loot loot[];
};

#endif
