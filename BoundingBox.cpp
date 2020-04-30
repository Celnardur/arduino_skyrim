#include "BoundingBox.h"

Box create_box(Pos * pos, byte width, byte height) {
    return {
        pos->pixel_x(),
        pos->pixel_x() + width,
        pos->pixel_y(),
        pos->pixel_y() + height
    };
}

bool has_collided(Box one, Box two) {
    return !((one.left > two.right || one.right < two.left) ||
    (one.top > two.bottom || one.bottom < two.top));
}

/*
// little algorthim for "sliding" the colliding box when there is a collision
Box box_slide(Box mobile, Box still) {
    // up down left right
    int direction[4] = {
        abs((int)mobile.bottom - (int)still.top),
        abs((int)mobile.top - (int)still.bottom),
        abs((int)mobile.right - (int)still.left),
        abs((int)mobile.left - (int)still.right),
     };

    // find the min direction
    int min_direction = 0;
    for (int i = 1; i < 4; i++) {
        if (direction[i] < direction[min_direction]) {
            min_direction = i;
        }
    }

    // slide the mobile box to avoid collision
    Box slid = mobile;
    switch (min_direction) {
    case 0:
        slid.bottom = still.top;
        slid.top = slid.bottom - (mobile.bottom - mobile.top);
        return slid;

    case 1:
        slid.top = still.bottom;
        return slid;

    case 2:
        slid.right = still.left;
        slid.left = slid.right - (mobile.right - mobile.left);
        return slid;

    case 3:
        slid.left = still.right;
        return slid;
    }
}
*/

void box_print(Box box) {
    Serial.println("Box {");
    Serial.println("    " + String(box.left));
    Serial.println("    " + String(box.right));
    Serial.println("    " + String(box.top));
    Serial.println("    " + String(box.bottom));
    Serial.println("}");
}

