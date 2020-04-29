#include "Input.h"

#define NUMBER_OF_BUTTONS 7

#define UP_BUTTON_PIN 2
#define RIGHT_BUTTON_PIN 3
#define DOWN_BUTTON_PIN 4
#define LEFT_BUTTON_PIN 5
#define START_BUTTON_PIN 6
#define SELECT_BUTTON_PIN 7
#define JOYSTICK_BUTTON_PIN 8
#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1

#define UP_MASK 0x01
#define RIGHT_MASK 0x02
#define DOWN_MASK 0x04
#define LEFT_MASK 0x08
#define START_MASK 0x10
#define SELECT_MASK 0x20
#define JOYSTICK_MASK 0x40

#define abs(x) (x < 0 ? -x : x)

void Input::construct() {
    // initialize variables
    this->buttons = 0;
    this->x_pos = 0;
    this->y_pos = 0;

    // find resting position of joystic
    uint32_t readings = 20;
    uint32_t x_sum = 0;
    uint32_t y_sum = 0;
    for (byte i = 0; i < readings; ++i) {
        x_sum += analogRead(JOYSTICK_X_PIN);
        y_sum += analogRead(JOYSTICK_Y_PIN);
        delay(20);
    }

    this->x_offset = x_sum / readings;
    this->y_offset = y_sum / readings;
}

void Input::setup() {
    // Setup Gamepad Inputs
    pinMode(UP_BUTTON_PIN, INPUT);
    pinMode(DOWN_BUTTON_PIN, INPUT);
    pinMode(LEFT_BUTTON_PIN, INPUT);
    pinMode(RIGHT_BUTTON_PIN, INPUT);
    pinMode(SELECT_BUTTON_PIN, INPUT);
    pinMode(START_BUTTON_PIN, INPUT);
    pinMode(JOYSTICK_BUTTON_PIN, INPUT);

    digitalWrite(UP_BUTTON_PIN, HIGH);
    digitalWrite(DOWN_BUTTON_PIN, HIGH);
    digitalWrite(LEFT_BUTTON_PIN, HIGH);
    digitalWrite(RIGHT_BUTTON_PIN, HIGH);
    digitalWrite(SELECT_BUTTON_PIN, HIGH);
    digitalWrite(START_BUTTON_PIN, HIGH);
    digitalWrite(JOYSTICK_BUTTON_PIN, HIGH);
}

void Input::process() {
    byte pins[NUMBER_OF_BUTTONS] = {
        UP_BUTTON_PIN, 
        RIGHT_BUTTON_PIN, 
        DOWN_BUTTON_PIN, 
        LEFT_BUTTON_PIN, 
        START_BUTTON_PIN,
        SELECT_BUTTON_PIN,
        JOYSTICK_BUTTON_PIN
    };
    byte masks[NUMBER_OF_BUTTONS] = {
        UP_MASK,
        RIGHT_MASK,
        DOWN_MASK,
        LEFT_MASK,
        START_MASK,
        SELECT_MASK,
        JOYSTICK_MASK
    };

    for (byte i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        if (digitalRead(pins[i]) != 1) {
            this->buttons = this->buttons | masks[i];
        }
    }

    uint16_t noise = 10;
    uint16_t reading = analogRead(JOYSTICK_X_PIN);
    int16_t pos = reading - this->x_offset;
    uint16_t mag = abs(pos);
    if (mag > noise && mag > abs(this->x_pos)) {
        this->x_pos = pos;
    }

    reading = analogRead(JOYSTICK_Y_PIN);
    pos = reading - this->y_offset;
    mag = abs(pos);
    if (mag > noise && mag > abs(this->y_pos)) {
        this->y_pos = pos; 
    }
}

void Input::clear() {
    this->buttons = 0;
    this->x_pos = 0;
    this->y_pos = 0;
}

void Input::print() const {
    Serial.println("Buttons: " + String(this->buttons));
    Serial.println("X: " + String(this->x_pos));
    Serial.println("Y: " + String(this->y_pos));
}

bool Input::up() const {
    return this->buttons & UP_MASK;
}

bool Input::right() const {
    return this->buttons & RIGHT_MASK;
}

bool Input::down() const {
    return this->buttons & DOWN_MASK;
}

bool Input::left() const {
    return this->buttons & LEFT_MASK;
}

bool Input::start() const {
    return this->buttons & START_MASK;
}

bool Input::select() const {
    return this->buttons & SELECT_MASK;
}

bool Input::joystick_button() const {
    return this->buttons & JOYSTICK_MASK;
}

#define ANALOG_MAX 1024

float Input::x() const {
    if (this->x_pos == 0) {
        return 0.0f;
    } else if ( this->x_pos < 0 ) {
        return (float)this->x_pos / this->x_offset;
    } else {
        return (float)this->x_pos / (ANALOG_MAX - this->x_offset);
    }
} 

float Input::y() const {
    if (this->y_pos == 0) {
        return 0.0f;
    }
    if ( this->y_pos < 0 ) {
        return (float)this->y_pos / this->y_offset;
    } else {
        return (float)this->y_pos / (ANALOG_MAX - this->y_offset);
    }
}

