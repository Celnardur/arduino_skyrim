// =======================================================================================
//            ND Game Control Starting Sketch for Notre Dame Droid Class
// =======================================================================================
//                          Last Revised Date: 03/15/2020
//                             Revised By: Prof McLaughlin
// =======================================================================================
// ---------------------------------------------------------------------------------------
//                          Libraries
// ---------------------------------------------------------------------------------------
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Input.h"
#include "Sprites.h"
#include "Constants.h"
#include "Game.h"

// ---------------------------------------------------------------------------------------
//                  Declare Scren (OLED) Items
// ---------------------------------------------------------------------------------------

//Intialize the Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------------------------------------------------------------------------------
//                 Declare Buzzer (Sound) Items
// ---------------------------------------------------------------------------------------
const byte buzzer PROGMEM = A2; //buzzer to arduino pin A2
long sound_millis = millis();
int sound_counter = 0;

#define LETTER_WIDTH 6
#define LETTER_HEIGHT 8

Input input;
Game game;

void setup() {
    Serial.begin(9600);

    // Set pin mode for the buzzer
    pinMode(buzzer, OUTPUT); // Set buzzer - pin 12 as an output

    // Setup Input Pins
    Input::setup();

    // Initialize the Display - Show Splash Screen
    display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
    display.display();
    delay(2000);

    // display splash screen
    display.clearDisplay();
    display.drawBitmap(
        (display.width() - DRAGON_WIDTH) / 2, 16, 
        dragon, DRAGON_WIDTH, DRAGON_HEIGHT, 1
    );

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor((display.width() - 6*LETTER_WIDTH*2) / 2, 0);
    display.println(F("Skyrim"));
    display.display();


    // load things
    input.construct();
    game.construct();

    while (input.get_buttons() == 0) {
        input.process();
    }
    input.clear();
}

void loop() {

    static unsigned long prevMillis = millis();
    static uint32_t tick = 0;
    static const long MS_PER_UPDATE PROGMEM = 100;

    input.process();

    if (millis() - prevMillis >= MS_PER_UPDATE) {
        prevMillis = millis();
        game.update(input, tick);
        //Serial.println(millis() - prevMillis);
        game.render(&display);
        input.clear();
        ++tick;
    }
    
    /*
    //Cycle buzzer sound up
    if (sound_millis + 200 < millis()) {
        sound_millis = millis();
        sound_counter++;
        tone(buzzer, ((sound_counter * 50) + 500)); // Send sound signal...
        if (sound_counter > 20) {
            sound_counter = 0;
        } 
    }
    */
}

/*
void testdrawbitmap(void) {
    display.clearDisplay();

    display.drawBitmap(
            (display.width()  - DOVAHKIIN_WIDTH ) / 2,
            (display.height() - DOVAHKIIN_HEIGHT) / 2,
            dovahkiin, DOVAHKIIN_WIDTH, DOVAHKIIN_HEIGHT, 1);
    display.display();
    delay(1000);
}
*/
