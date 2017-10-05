/**********************ETUDE 2 CART 360 2017*******************************
   WELCOME!
   THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
   WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK.
   THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
   THERE ARE 5 POSSIBLE MODES
   0 ==  reset    ==   led off == also resets
   1 ==  live     ==   led BLUE
   2 ==  record   ==   led RED
   3 ==  play     ==   led GREEN
   4 ==  loopMODE ==   led PURPLE

   ADDITIONALLY - WHEN THE USER CHANGES MODE,
   THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

   PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
   DO NOT ADD ANY MORE FUNCTION DEFINITIONS
   ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
   THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
   PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
   GOOD LUCK!
*/
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN //double check these are 
//right when connected

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

// constant for max number of notes in array
#define MAX_NOTES 16  //array of max notes for player

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES];
int mode = 0; // start at off

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);
  //IMPLEMENT

  //for rbg color outputs
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);

  //digital output
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600); //used this to determine "noteInput" value
}

/**********************LOOP() DO NOT CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change the loop - it establishes the flow of the program
   We call here 3 functions repeatedly:
   1: chooseMode(): this function will determine the mode that your program is in
   based on if the button (linked to the BUTTON_MODE_PIN) was pressed
   2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
   3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   Read the value from the Button (linked to the BUTTON_MODE_PIN) and
   if is being pressed then change the mode variable.
   REMEMBER:
   mode == 0 is reset
   mode == 1 is live
   mode == 2 is record
   mode == 3 is play
   mode == 4 is loopMode
   Every time the user presses the button, the program will go to the next mode,
   once it reaches 4, it should go back to mode == 0.
   (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode() {
  // IMPLEMENT

  int buttonState = digitalRead(BUTTON_MODE_PIN);
  //if the button is in a certain state and the button is pressed
  //switch over to the next state and continue

  if (buttonState == HIGH) {
    if (mode == 0) {
      mode = 1;
    }
    else if (mode == 1) {
      mode = 2;
    }
    else if (mode == 2) {
      mode = 3;
    }
    else if (mode == 3) {
      mode = 4;
    }
    else if (mode == 4) {
      mode = 0; //reset
    }
    delay(200); //add delay to slow things down
  }
}

/******************SETRGB(): IMPLEMENT *********************************
   INSTRUCTIONS:
   Depending on the value of the mode variable:
   if the mode is 0 - RGB LED IS OFF
   if the mode is 1 - RGB LED IS BLUE
   if mode is 2 - RGB LED IS RED
   if mode is 3 - RGB LED IS GREEN
   if mode is 4 - RGB LED iS PURPLE
   YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{

  //set up the switches for each rgb color
  switch (mode) { //mode = 1,2,3 or 4

    case 0: //whole thing off
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, LOW);
      break; //end of loop

    case 1: //blue
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, HIGH);
      break; //end of loop

    case 2: //red
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, LOW);
      break; //end of loop

    case 3: //green
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, LOW);
      break; //end of loop

    case 4: //purple
      analogWrite(LED_PIN_R, 30); //alalog write allows to put numbers. this allows my to make purple
      digitalWrite(LED_PIN_G, LOW);
      analogWrite(LED_PIN_B, HIGH);
      break; //end of loop
  }
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
   There are 4 possibilities
   1: reset(): this function will reset any arrays etc, and will do nothing else
   2: live(): this function will play the corresponding notes
   to the user pressing the respective buttons.
   NOTE:: the notes played are NOT stored
   3: record(): this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   4: play(): this function will playback any notes stored in the array that were recorded
   in the previous mode
   5: loopMode(): this function will playback any notes stored in the array that were recorded,
   BUT unlike the previous mode, you can choose in which sequence the notes are played.
   REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if (mode == 0) { //if set to mode 0 (off/no color) reset the board
    reset();
  }
  else if (mode == 1) { // or else if set to mode 1 (blue) enter live play
    live();
  }
  else if (mode == 2) { //or else if set to mode 2 (red) enter record
    record();
  }

  else if (mode == 3) { //or else if set to mode 3 (green) play recording
    play();
  }

  else if (mode == 4) { //or else if set to mode 4 (purple) plat random notes
    loopMode();
  }
}
/******************RESET(): IMPLEMENT **************************************
   INSTRUCTIONS:
   this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  // IMPLEMENT
  countNotes = 0;
  //reset notes back to zero. countNotes value augemted because of loop therfore must be reset back to 0 to work again
}
/******************LIVE(): IMPLEMENT **************************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   NOTE:: the notes played are NOT stored
   SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
   THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
  //IMPLEMENT
  int noteInput;
  noteInput = analogRead(NOTE_IN_PIN);
  tone(BUZZER_PIN, noteInput, duration);
}
/******************RECORD(): IMPLEMENT **********************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
   AND - output the note to the buzzer using the tone() function
   THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  // IMPLEMENT
  int noteInput;
  noteInput = analogRead(NOTE_IN_PIN);

  //used Serial.println(noteInput) to determine this value (203). This is the lowest frequency
  if (countNotes < MAX_NOTES && noteInput >= 203) {
    notes[countNotes] = noteInput;
    countNotes++;
    tone(BUZZER_PIN, noteInput, duration);
    delay(duration);
  }
}
/******************PLAY(): IMPLEMENT ************************************
   INSTRUCTIONS:
   this function will playback any notes stored in the array that were recorded
   in the previous mode
   SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
   READ each value IN ORDER
   AND output each note to the buzzer using the tone() function
   ALSO: as long as we are in this mode, the notes are played over and over again
   BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  // IMPLEMENT
  //use boolean because theres only 2 states
  //if soundMode is true, play this loop. If button gets pressed, break the loop and soundMode changes to false
  boolean  soundMode = true;
  while (soundMode) {
    for (int i = 0; i <= countNotes; i++) {
      tone(BUZZER_PIN, notes[i], duration);
      delay(duration);
      if (digitalRead(BUTTON_MODE_PIN) == HIGH) {
        soundMode = false;
        break; //end of loop
      }
    }
  }
}
/******************LOOPMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   this function will playback any notes stored in the array that were recorded
   in the previous mode
   SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
   READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
   AND output each note to the buzzer using the tone() function
   ALSO: as long as we are in this mode, the notes are played over and over again
   BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void loopMode()
{
  //IMPLEMENT
  boolean  soundMode = true;
  //if soundMode is true, play this loop that generates random values which in turn makes random sounds.
  //If button is pressed again, change soundMode to false
  while (soundMode) {
    for (int i = 0; i <= countNotes; i++) {
      //set a variable that grabs random values for notes
      int randomNote = random(0, i);
      tone(BUZZER_PIN, notes[(randomNote)], duration);
      delay(duration);
      if (digitalRead(BUTTON_MODE_PIN) == HIGH) {
        soundMode = false;
        break; //end of loop
      }
    }
  }
}

/**************************************************************************/
/* Overview: 
 * Due to the motion of electrons passing through the resistors, it creates terminal noise which is how the sounds are being created
 * When sounds are playing, it can be seen as a representation of current running through the circuit
 * The more ohms in the resister, the deeper the sound. 
 * This change is affectd by how many Ohms is in the resistor, more ohms = less current passing throught which t= less therminal noise. 
 * The highest resistors does not generate any sound because of the very low frequency.  
 * The button on my circuit that outputs highest sound is using only the first resistor and thats why the sound it high 
 * The button on my circuit that is outputting the lowest sound is using all the resistors on the resistor ladder
 * All these resistors are making less voltage pass through to the last button therefore low sound.
 * Everytime a button is pressed, current is being sent through
 */



