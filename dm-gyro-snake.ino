#define LED_PIN 13

#define C1 2 // Anode, 1st bit (2^1)
#define C2 3 // Anode, 2nd bit (2^2)
#define C3 4 // Anode, 3rd bit (2^3)

#define A1 6 // Cathode, 1st bit (2^1)
#define A2 7 // Cathode, 2nd bit (2^2)
#define A3 8 // Cathode, 3rd bit (2^3)

#define FREQ 60 // Hz

short int catPins[3] = {2, 3, 4};   // pins on the ATmega328P
short int anPins[3] = {6, 7, 8};    // pins on the ATmega328P

short int inCoordX = 0;
short int inCoordY = 0;



  // LED Pins:        {6, 10, 4, 3, 13}
  // c_pins decimal:  {2, 3, 1, 0, 4}
short int c_pins[5] = {2, 3, 1, 0, 4};
//  short int c_pins[5] = {010, 011, 001, 000, 100};

  // LED Pins:        {9, 14, 8, 5, 1, 7, 2}  <- dot matrix pins
  // a_pins decimal:  {5, 6, 4, 2, 0, 3, 1}   <- decoder pins
short int a_pins[7] = {5, 6, 4, 2, 0, 3, 1};
//  short int a_pins[7] = {101, 110, 100, 010, 000, 011, 001};

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
void dispLED(short int loc_x, short int loc_y) {
  
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

  short int x;
  short int y;
  
  x = a_pins[loc_x];
  y = c_pins[loc_y];
  
  for (int i; i<3; i++) {
    if (x&1) {
      digitalWrite(anPins[i], HIGH);
    } else {
      digitalWrite(anPins[i], LOW);
    }

    if (y&1) {
      digitalWrite(catPins[i], HIGH);
    } else {
      digitalWrite(catPins[i], LOW);
    }

    x >> 1;
    y >> 1;
  }
}

void setup() {

  Serial.begin(9600);
  
  pinMode(catPins[0], OUTPUT);
  pinMode(catPins[1], OUTPUT);
  pinMode(catPins[2], OUTPUT);
  
  pinMode(anPins[0], OUTPUT);
  pinMode(anPins[1], OUTPUT);
  pinMode(anPins[2], OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
          // read the incoming byte:
          inCoordX = Serial.read();

          Serial.print("I received: ");
          Serial.println(inCoordX, DEC);
  }

  dispLED(5, 2);

  
}


