#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Pos.h"

// cooridnates in pixels
struct Box {
    byte left;
    byte right;
    byte top;
    byte bottom;
};

Box create_box(Pos * pos, byte width, byte height);

bool has_collided(Box one, Box two);

// little algorthim for "sliding" the colliding box when there is a collision
Box box_slide(Box mobile, Box still);

void box_print(Box box);

#endif
