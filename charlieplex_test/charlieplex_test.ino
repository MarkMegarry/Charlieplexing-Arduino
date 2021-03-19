//INTENDED FOR USE WITH 12-LED CHARLIEPLEX MATRIX
//WARNING: DO NOT USE WITH UNPAIRED LEDS, AS THE REVERSE VOLTAGE WITHOUT THE FORWARD VOLTAGE DROP OF AN LED IN THE OPPOSITE POLARITY IN PARALLEL MAY DESTROY LEDS
#define line1 2
#define line2 3
#define line3 4
#define line4 5
#define commonDelay 100 

//Each entry defines an int to be passed to setOutputs()
//Leftmost 4 bits determine pin modes, rightmost 4 bits determine digitalWrite states
//Roughly according to 4-pin schematic at http://www.multiwingspan.co.uk/arduino.php?page=vbcharlie , some pair numbers might be swapped.
uint8_t LED_patterns[12] =  { 0b00110001,
                              0b00110010,
                              0b01100010,
                              0b01100100,
                              0b11001000,
                              0b11000100,
                              0b01010100,
                              0b01010001,
                              0b10100010,
                              0b10101000,
                              0b10010001,
                              0b10011000
                              }; 
void setup() {
  //Empty
}

void loop() {
  for(int x = 0; x < 12; x++){
    setOutputs(LED_patterns[x]);
    delay(commonDelay);
  }
}

/**********************************************************************************************************************
 * Uses LED_address to determine whether each line pin is an input or output, and whether to set 
 * each pin high or low.
 * 
 * Leftmost 4 bits determine input or output, 0 = input, 1 = output. LED_address bit 4 is line1 and bit 7 is line4
 * Rightmost 4 bits determine digitalWrite high or low, 0 = low, 1 = high. LED_address bit 0 is line1 and bit 3 is line4 
 ***********************************************************************************************************************/
void setOutputs(uint8_t LED_address){ 
  int pinArray[4] = {line1, line2, line3, line4};

  //Set pin states and write outputs
  for(int x = 0; x < 4; x++){
    if(customReadBit(LED_address, x + 4)){   //If the corresponding bit of LED_address is high
      pinMode(pinArray[x], OUTPUT);   //Set the pin mode according to the modeBits
    }
    else{                             //If corresponding bit of LED_address is low
      pinMode(pinArray[x], INPUT);
    }
    digitalWrite(pinArray[x], customReadBit(LED_address, x));  //Set output according to LED_address
  }
}

int customReadBit(int input, int bitPos){ //Reads bit bitpos of input where 0 is LSB
  return (input >> bitPos) & 1;
}
