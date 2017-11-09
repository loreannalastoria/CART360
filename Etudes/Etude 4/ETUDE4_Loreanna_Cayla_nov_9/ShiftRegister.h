/*----------------------------------------------------------------------------*/
/*------------------------------ SHIFT REGISTER ------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------      IMPLEMENT THE SHIFT REGISTER FUNCTIONALITY        ----------*/
/*----------          ******** ATTRIBUTE YOUR CODE ********         ----------*/
/*----------------------------------------------------------------------------*/

#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_

#include "Constants.h"

/* SHIFT REGISTER IC PIN OUTS
        __
  Q1 -|    |- VCC
  Q2 -|    |- Q0
  Q3 -|    |- DS
  Q4 -|    |- OE
  Q5 -|    |- ST_CP
  Q6 -|    |- SH_CP
  Q7 -|    |- MR
 GND -| __ |- Q'

  Key:
  Q0 - Q7: Parallel Out Pins
  Q': Cascade Pin
  DS: Serial Data In Pin
  OE: Output Enable (GND)
  ST_CP: Latch Pin
  SH_CP: Clock Pin
  MR: Master Reset (VCC)
*/

/* PINS FOR SHIFT REG */
// ST_CP of 74HC595    Pin 12
#define LATCH_PIN 6
// SH_CP of 74HC595    pin 11
#define CLOCK_PIN 8
// DS of 74HC595       pin 14
#define DATA_PIN 7

/* CONSTANT FOR EMPTY*/
#define EMPTY B00000001

/* DEFINE AND INITIALIZE THE ARRAY WITH THE NECESSARY VALUES */
// Hex Character from 0 - F
byte hexArray[16] = 
{ 
   B1111110,      //0
   B0110000,     // 1
   B1101101,     // 2
   B1111001,     // 3
   B0110011,     // 4
   B1011011,     // 5
   B1011111,     // 6
   B1110000,     // 7          //1 = on and 0 = off
   B1111111,     // 8          //represents each light on the 7 Segment LED and when to turn it on
   B1110011,     // 9
   B1110111,     // A
   B0011111,     // B
   B1001110,     // C
   B0111101,     // D
   B1001111,     // E
   B1000111      // F
  };    

void setupShiftRegister() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  }
  
/******************sendToShiftRegister *******************************
TODO:: IMPLEMENT THE FUNCTIONALITY TO SEND THE CORRECT DATA TO 
SHIFT REG - BASED ON THE POT VAL
********************************************************************/
void sendToShiftRegister(int pot)
{
    int value = pot;
    digitalWrite(LATCH_PIN, LOW); //when latch pin is LOW, starts sending data
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value); //shiftOut is arduino fuction that pushes data through
    digitalWrite(LATCH_PIN, HIGH); //return to original state
    delay(200);

  
  //pot is the value on the potentiometer, so depending on the pot it will store in the appropriate slot
}

/******************READ FROM POT*********************************
TO DO:: GET VALUE FROM POT AND ENSURE THE VALUE RETURNED IS A VALID VALUE 
********************************************************************/
int getAnalog() {
 int val = analogRead(A1) / 8;
 
  //value between 0-1023 that fits in 16
  //potentiometer is analog
  //1023 states in an alalog read
}

#endif /* SHIFTREGISTER_H_ */
