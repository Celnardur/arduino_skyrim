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

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char logo_bmp[] PROGMEM ={ 
    B00000000, B11000000,
    B00000001, B11000000,
    B00000001, B11000000,
    B00000011, B11100000,
    B11110011, B11100000,
    B11111110, B11111000,
    B01111110, B11111111,
    B00110011, B10011111,
    B00011111, B11111100,
    B00001101, B01110000,
    B00011011, B10100000,
    B00111111, B11100000,
    B00111111, B11110000,
    B01111100, B11110000,
    B01110000, B01110000,
    B00000000, B00110000 
};

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

    // Draw a single pixel in white
    display.drawPixel(10, 10, SSD1306_WHITE);
    display.display();
    delay(1000);

    testdrawline();      // Draw many lines

    testdrawrect();      // Draw rectangles (outlines)

    testfillrect();      // Draw rectangles (filled)

    testdrawcircle();    // Draw circles (outlines)

    testfillcircle();    // Draw circles (filled)

    testdrawroundrect(); // Draw rounded rectangles (outlines)

    testfillroundrect(); // Draw rounded rectangles (filled)

    testdrawtriangle();  // Draw triangles (outlines)

    testfilltriangle();  // Draw triangles (filled)

    testdrawchar();      // Draw characters of the default font

    testdrawstyles();    // Draw 'stylized' characters

    testscrolltext();    // Draw scrolling text

    testdrawbitmap();    // Draw a small bitmap image

    // Invert and restore display, pausing in-between
    display.invertDisplay(true);
    delay(1000);
    display.invertDisplay(false);
    delay(1000);
}

void loop() {

    //Cycle buzzer sound up
    if (sound_millis + 200 < millis()) {
        sound_millis = millis();
        sound_counter++;
        tone(buzzer, ((sound_counter * 50) + 500)); // Send sound signal...
        if (sound_counter > 20) {
            sound_counter = 0;
        } 
    }

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

    control_input = analogRead(joystick_x);
    if (control_input < 500 || control_input > 515) {
        Serial.println("Josystick X Value: " + String(control_input));
    }

    control_input = analogRead(joystick_y);
    if (control_input < 500 || control_input > 515) {
        Serial.println("Josystick X Value: " + String(control_input));
    }
}

void testdrawline() {
    int16_t i;

    display.clearDisplay(); // Clear display buffer

    for(i=0; i<display.width(); i+=4) {
        display.drawLine(0, 0, i, display.height()-1, SSD1306_WHITE);
        display.display(); // Update screen with each newly-drawn line
        delay(1);
    }
    for(i=0; i<display.height(); i+=4) {
        display.drawLine(0, 0, display.width()-1, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for(i=0; i<display.width(); i+=4) {
        display.drawLine(0, display.height()-1, i, 0, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for(i=display.height()-1; i>=0; i-=4) {
        display.drawLine(0, display.height()-1, display.width()-1, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for(i=display.width()-1; i>=0; i-=4) {
        display.drawLine(display.width()-1, display.height()-1, i, 0, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for(i=display.height()-1; i>=0; i-=4) {
        display.drawLine(display.width()-1, display.height()-1, 0, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for(i=0; i<display.height(); i+=4) {
        display.drawLine(display.width()-1, 0, 0, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for(i=0; i<display.width(); i+=4) {
        display.drawLine(display.width()-1, 0, i, display.height()-1, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000); // Pause for 2 seconds
}

void testdrawrect(void) {
    display.clearDisplay();

    for(int16_t i=0; i<display.height()/2; i+=2) {
        display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
        display.display(); // Update screen with each newly-drawn rectangle
        delay(1);
    }

    delay(2000);
}

void testfillrect(void) {
    display.clearDisplay();

    for(int16_t i=0; i<display.height()/2; i+=3) {
        // The INVERSE color is used so rectangles alternate white/black
        display.fillRect(i, i, display.width()-i*2, display.height()-i*2, SSD1306_INVERSE);
        display.display(); // Update screen with each newly-drawn rectangle
        delay(1);
    }

    delay(2000);
}

void testdrawcircle(void) {
    display.clearDisplay();

    for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
        display.drawCircle(display.width()/2, display.height()/2, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfillcircle(void) {
    display.clearDisplay();

    for(int16_t i=max(display.width(),display.height())/2; i>0; i-=3) {
        // The INVERSE color is used so circles alternate white/black
        display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
        display.display(); // Update screen with each newly-drawn circle
        delay(1);
    }

    delay(2000);
}

void testdrawroundrect(void) {
    display.clearDisplay();

    for(int16_t i=0; i<display.height()/2-2; i+=2) {
        display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
                display.height()/4, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfillroundrect(void) {
    display.clearDisplay();

    for(int16_t i=0; i<display.height()/2-2; i+=2) {
        // The INVERSE color is used so round-rects alternate white/black
        display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
                display.height()/4, SSD1306_INVERSE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testdrawtriangle(void) {
    display.clearDisplay();

    for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
        display.drawTriangle(
                display.width()/2  , display.height()/2-i,
                display.width()/2-i, display.height()/2+i,
                display.width()/2+i, display.height()/2+i, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfilltriangle(void) {
    display.clearDisplay();

    for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
        // The INVERSE color is used so triangles alternate white/black
        display.fillTriangle(
                display.width()/2  , display.height()/2-i,
                display.width()/2-i, display.height()/2+i,
                display.width()/2+i, display.height()/2+i, SSD1306_INVERSE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testdrawchar(void) {
    display.clearDisplay();

    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' font

    // Not all the characters will fit on the display. This is normal.
    // Library will draw what it can and the rest will be clipped.
    for(int16_t i=0; i<256; i++) {
        if(i == '\n') display.write(' ');
        else          display.write(i);
    }

    display.display();
    delay(2000);
}

void testdrawstyles(void) {
    display.clearDisplay();

    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    display.println(F("Hello, world!"));

    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.println(3.141592);

    display.setTextSize(2);             // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.print(F("0x")); display.println(0xDEADBEEF, HEX);

    display.display();
    delay(2000);
}

void testscrolltext(void) {
    display.clearDisplay();

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.println(F("scroll"));
    display.display();      // Show initial text
    delay(100);

    // Scroll in various directions, pausing in-between:
    display.startscrollright(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrollleft(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrolldiagright(0x00, 0x07);
    delay(2000);
    display.startscrolldiagleft(0x00, 0x07);
    delay(2000);
    display.stopscroll();
    delay(1000);
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
