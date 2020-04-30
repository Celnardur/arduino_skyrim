#include "Pos.h"

#define bound(set, to, max, min) \
    if ((to) > (max)) { (set) = (max); } \
    else if ((to) < (min)) { (set) = (min); } \
    else { (set) = (to); }

Pos Pos::add_pixel(int32_t x, int32_t y) {
    int32_t newx = this->x + x*PIXEL_SIZE;
    int32_t newy = this->y + y*PIXEL_SIZE;
    bound(this->x, newx, U16_MAX, 0)
    bound(this->y, newy, U16_MAX, 0)
    return *this;
}

Pos Pos::add(int32_t x, int32_t y) {
    int32_t newx = this->x + x;
    int32_t newy = this->y + y;
    bound(this->x, newx, U16_MAX, 0)
    bound(this->y, newy, U16_MAX, 0)
    return *this;
}

void Pos::print() const {
    Serial.print("X: " + String(this->x/PIXEL_SIZE));
    Serial.println("Y: " + String(this->y/PIXEL_SIZE));
}
