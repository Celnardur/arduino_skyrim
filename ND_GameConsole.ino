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

// ---------------------------------------------------------------------------------------
//                  Declare Scren (OLED) Items
// ---------------------------------------------------------------------------------------
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Intialize the Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------------------------------------------------------------------------------
//                 Declare Buzzer (Sound) Items
// ---------------------------------------------------------------------------------------
const byte buzzer PROGMEM = A2; //buzzer to arduino pin A2
long sound_millis = millis();
int sound_counter = 0;

// ---------------------------------------------------------------------------------------
//                 Declare Gamepad Button Items
// ---------------------------------------------------------------------------------------
const PROGMEM byte up_button = 2;
const PROGMEM byte right_button = 3;
const PROGMEM byte down_button = 4;
const PROGMEM byte left_button = 5;
const PROGMEM byte start_button = 6;
const PROGMEM byte select_button = 7;
const PROGMEM byte joystick_button = 8;
const PROGMEM byte joystick_x = A0;
const PROGMEM byte joystick_y = A1;

// ---------------------------------------------------------------------------------------
//                 Display Routine Variable
// ---------------------------------------------------------------------------------------
#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define DOVAHKIIN_HEIGHT 8
#define DOVAHKIIN_WIDTH 8
static const unsigned char dovahkiin[] PROGMEM = {
    B10000010,
    B01000100,
    B01101100,
    B11000110,
    B10010010,
    B10111010,
    B11010110,
    B01101100,
};

void setup() {
    Serial.begin(9600);

    // Set pin mode for the buzzer
    pinMode(buzzer, OUTPUT); // Set buzzer - pin 12 as an output

    // Setup Gamepad Inputs
    pinMode(up_button, INPUT);
    pinMode(down_button, INPUT);
    pinMode(left_button, INPUT);
    pinMode(right_button, INPUT);
    pinMode(select_button, INPUT);
    pinMode(start_button, INPUT);
    pinMode(joystick_button, INPUT);

    digitalWrite(up_button, HIGH);
    digitalWrite(down_button, HIGH);
    digitalWrite(left_button, HIGH);
    digitalWrite(right_button, HIGH);
    digitalWrite(select_button, HIGH);
    digitalWrite(start_button, HIGH);
    digitalWrite(joystick_button, HIGH);

    // Initialize the Display - Show Splash Screen
    display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
    display.display();
    delay(2000);
    display.clearDisplay();

    testdrawbitmap();    // Draw a small bitmap image
}

void loop() {


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

    // Print to the Serial Monitor all the gamepad inputs
    output_gamepad_inputs();
}

void output_gamepad_inputs() {
    int control_input = 0;

    control_input = digitalRead(up_button);
    if (control_input != 1) {
        Serial.println("Up Button Pushed");    
    }

    control_input = digitalRead(down_button);
    if (control_input != 1) {
        Serial.println("Down Button Pushed");    
    }

    control_input = digitalRead(left_button);
    if (control_input != 1) {
        Serial.println("Left Button Pushed");    
    }

    control_input = digitalRead(right_button);
    if (control_input != 1) {
        Serial.println("Right Button Pushed");    
    }

    control_input = digitalRead(select_button);
    if (control_input != 1) {
        Serial.println("Select Button Pushed");    
    }

    control_input = digitalRead(start_button);
    if (control_input != 1) {
        Serial.println("Start Button Pushed");    
    }

    control_input = digitalRead(joystick_button);
    if (control_input != 1) {
        Serial.println("Joystick Button Pushed");    
    }

    // hovers around 492
    control_input = analogRead(joystick_x);
    if (control_input < 475 || control_input > 530) {
        Serial.println("Josystick X Value: " + String(control_input));
    }

    // hovers around 517
    control_input = analogRead(joystick_y);
    if (control_input < 475 || control_input > 530) {
        Serial.println("Josystick Y Value: " + String(control_input));
    }
}

void testdrawbitmap(void) {
    display.clearDisplay();

    display.drawBitmap(
            (display.width()  - DOVAHKIIN_WIDTH ) / 2,
            (display.height() - DOVAHKIIN_HEIGHT) / 2,
            dovahkiin, DOVAHKIIN_WIDTH, DOVAHKIIN_HEIGHT, 1);
    display.display();
    delay(1000);
}
