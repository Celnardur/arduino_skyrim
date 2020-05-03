#ifndef MOVE_H
#define MOVE_H

struct Move {
   int32_t speed;
   float x;
   float y;
};

#define print_move(mv) \
    Serial.println("Move {");\
    Serial.println("    " + String(mv.speed));\
    Serial.println("    " + String(mv.x));\
    Serial.println("    " + String(mv.y));\
    Serial.println("}");



#endif
