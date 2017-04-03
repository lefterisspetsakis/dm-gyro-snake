#define LED_PIN 13

#define C1 2 // Anode, 1st bit (2^1)
#define C2 3 // Anode, 2nd bit (2^2)
#define C3 4 // Anode, 3rd bit (2^3)

#define A1 6 // Cathode, 1st bit (2^1)
#define A2 7 // Cathode, 2nd bit (2^2)
#define A3 8 // Cathode, 3rd bit (2^3)

#define FREQ 60 // Hz


void setup() {
  // put your setup code here, to run once:
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  // LED Pins:        {6, 10, 4, 3, 13}
  // c_pins decimal:  {2, 3, 1, 0, 4}
  short int c_pins[5] = {010, 011, 001, 000, 100};

  // LED Pins:        {9, 14, 8, 5, 1, 7, 2}
  // a_pins decimal:  {5, 6, 4, 2, 0, 3, 1}
  short int a_pins[7] = {101, 110, 100, 010, 000, 011, 001};
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*   LED Numbering
 *   ---__---__---    <-- physical notches on dot matrix
 *   0 1 2 3 4 5 6        that denote the orientation
 *   1 . . . . . .
 *   2 . . . . . .
 *   3 . . . . . .
 *   4 . . . . . .
 *   ---__---__---
 */
void dispLED(x,y) {
  
}

