#ifndef SPRITES_H
#define SPRITES_H

#define DRAGON_HEIGHT 45
#define DRAGON_WIDTH 24

#define DOVAHKIIN_HEIGHT 8
#define DOVAHKIIN_WIDTH 8

static const unsigned char dovahkiin[8] PROGMEM = {
    B10000010,
    B01000100,
    B01101100,
    B11000110,
    B10010010,
    B10111010,
    B11010110,
    B01101100,
};

static const unsigned char dragon[] PROGMEM = {
    B00000000, B10000001, B00000000,
    B00000000, B11000011, B00000000,
    B00000001, B10100101, B10000000,
    B00000001, B00000000, B10000000,
    B00000001, B00100000, B10000000,
    B00000011, B00100000, B11000000,
    B00000010, B00111100, B01000000,
    B00000110, B00111000, B01100000,
    B00000110, B01111100, B01100000,
    B00001110, B01100110, B01110000,
    B00001100, B01000010, B00110000,
    B00011100, B00000010, B00111000,
    B00011110, B00001110, B01111000,
    B00111011, B00111000, B11011100,
    B00111000, B00100000, B00011100,
    B01111000, B01100000, B00011110,
    B01110000, B00110000, B00001110,
    B11110011, B00110001, B10001111,
    B11110001, B10111011, B00001111,
    B11111001, B10111011, B00011111,
    B01111111, B11111111, B11111110,
    B01111111, B11111111, B11111110,
    B00111111, B11111111, B11111100,
    B00111101, B11111111, B10111100,
    B00011100, B10111101, B00111000,
    B00011100, B10011101, B00111000,
    B00011100, B00011000, B00111000,
    B00001100, B00001000, B00110000,
    B00001100, B00001100, B00110000,
    B00000110, B00001100, B01100000,
    B00000111, B00001100, B11100000,
    B00000011, B10001001, B11000000,
    B00000011, B10011001, B11000000,
    B00000001, B10010001, B10000000,
    B00000001, B10110001, B10000000,
    B00000000, B10110001, B00000000,
    B00000000, B10010001, B00000000,
    B00000000, B00011000, B00000000,
    B00000000, B00110000, B00000000,
    B00000000, B01100000, B00000000,
    B00000000, B00100000, B00000000,
    B00000000, B00111110, B00000000,
    B00000000, B00011100, B00000000,
    B00000000, B00011100, B00000000,
    B00000000, B00001000, B00000000,
};

#endif