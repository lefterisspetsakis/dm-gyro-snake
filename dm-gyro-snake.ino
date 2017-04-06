#define LED_GRE 13
#define LED_RED 9
#define LED_YEL 10

#define BUTTON_PIN 5

#define MAX_EVENTS 8
#define FREQ 60 // Hz

short int catPins[3] = {2, 3, 4};   // pins on the ATmega328P
short int anPins[3] = {6, 7, 8};    // pins on the ATmega328P

// LED Pins:   {13, 3, 4, 10, 6}  <- dot matrix pins
int c_pins[5] = {4, 0, 1, 3, 2};

// LED Pins:    {9, 14, 8, 5, 1, 7, 2}  <- dot matrix pins
int a_pins[7] = {5, 6, 4, 2, 0, 3, 1};

/*   LED Numbering
 *   ---__---__---    <-- physical notches on dot matrix
 *   0 1 2 3 4 5 6  (x)   that denote the orientation
 *   1 . . . . . .
 *   2 . . . . . .
 *   3 . . . . . .
 *   4 . . . . . .
 *   
 *  (y)
 *   ---__---__---
 */


struct ST_btn   // ST means state of button
{
  short int pressed;
  short int led_on;
};

class CLBtnReset
{
  private:
    int sleep_time = 1; // 1 millisecond
    ST_btn state;
  public:
    int btnPressed()
    {
      if (digitalRead(BUTTON_PIN) == HIGH)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
    void checkBtn()
    {
      if ((state.pressed == 0) && (btnPressed() == 1))
      {
        state.pressed = 1;
        if (state.led_on == LED_YEL)
        {
          state.led_on = LED_RED;
          digitalWrite(LED_RED, HIGH);
          digitalWrite(LED_YEL, LOW);
        }
        else if (state.led_on == LED_RED)
        {
          state.led_on = LED_YEL;
          digitalWrite(LED_YEL, HIGH);
          digitalWrite(LED_RED, LOW);
        }
      }
      if ((state.pressed == 1) && (btnPressed() == 0))
      {
        state.pressed = 0;
      }
    }
};


void dispLED(short int loc_x, short int loc_y)
{
  /* loc_x is a coordinate that respects the numbering
   * scheme above.
   * 
   * x is the anode pin number (corresponding to loc_x)
   * on the decoder that drives the dot matrix (LEDs)
   * 
   * 
   * loc_y is a coordinate that respects the numbering
   * scheme above.
   * 
   * y is the cathode pin number (corresponding to loc_y)
   * on the decoder that drives the dot matrix (LEDs)
   */

  int x;
  int y;
  
  x = a_pins[loc_x];
  y = c_pins[loc_y];
  
  for (int i; i<3; i++)
  {
    if (x&1)
    {
      digitalWrite(anPins[i], HIGH);
    }
    else
    {
      digitalWrite(anPins[i], LOW);
    }

    if (y&1)
    {
      digitalWrite(catPins[i], HIGH);
    }
    else
    {
      digitalWrite(catPins[i], LOW);
    }

    x = x >> 1;
    y = y >> 1;
  }
}

//void scheduler()
//{
//  for (short int i=0; i<MAX_EVENTS; i++)
//  {
//    if (tasks[i].time >= millis())
//    {
//      tasks[i].update(tasks[i].state);
//    }
//  }
//}

void setup()
{
  Serial.begin(9600);

  // setup cathode pins (dot matrix)
  pinMode(catPins[0], OUTPUT);
  pinMode(catPins[1], OUTPUT);
  pinMode(catPins[2], OUTPUT);

  // setup anode pins (dot matrix)
  pinMode(anPins[0], OUTPUT);
  pinMode(anPins[1], OUTPUT);
  pinMode(anPins[2], OUTPUT);

  // setup debug leds
  pinMode(LED_GRE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YEL, OUTPUT);

  // setup button
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  dispLED(0, 3);
  CLBtnReset btnReset;
  while (true)
  {

    btnReset.checkBtn();
//    scheduler();
    
  }
}


