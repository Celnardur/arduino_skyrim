#ifndef ENTITY_H
#define ENTITY_H

#include "Pos.h"
#include "Move.h"
#include "Map.h"

enum Type {
    DEFAULT_MONSTER,
    ATTACK,
};

#define TYPE_MASK 0x07
#define DEAD_MASK 0x08
#define CREATED_MASK 0x10

class Entity {
public:
    // tile cooridnates
    void set(byte x, byte y, byte flags);
    void make_empty() { this->flags = 0x00; }

    Pos * get_pos_pointer() { return &this->pos; };
    byte get_width() const { return MONSTER_WIDTH; };
    byte get_height() const { return MONSTER_HEIGHT; };
    bool is_dead() const { return this->flags & DEAD_MASK; };
    bool was_created() const { return this->flags & CREATED_MASK; };
    
    Move ai(Pos player, const Map &map) const;   

    void render(Adafruit_SSD1306 * display, int origin_x, int origin_y);

private:
    Pos pos;
    byte flags;
};

#endif
