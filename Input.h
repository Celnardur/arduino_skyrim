#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>


class Input {
public:
    void construct();
    static void setup();
    void process();
    void clear();
    void print() const;

    byte get_buttons() const {return this->buttons;}

    bool up() const;
    bool right() const;
    bool down() const;
    bool left() const;
    bool start() const;
    bool select() const;
    bool joystick_button() const;

    float x() const;
    float y() const;

private:
    byte buttons;
    int16_t x_pos;
    int16_t y_pos;
    uint16_t x_offset;
    uint16_t y_offset;
};

#endif
