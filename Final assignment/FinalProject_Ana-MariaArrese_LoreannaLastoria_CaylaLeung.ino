//Shift - Ana-Maria Arrese, Loreanna Lastoria, Cayla Leung

//include stepper class for motor
#include <Stepper.h>

//declare stepper motor steps
#define motorSteps 200

//pins for stepper number 1
#define motorPin4 4
#define motorPin5 5
#define motorPin6 6
#define motorPin7 7


//pins for stepper number 2
#define motorPin8 8
#define motorPin9 9
#define motorPin10 10
#define motorPin11 11

//pins for stepper number 3
#define motorPin14 44
#define motorPin15 46
#define motorPin16 48
#define motorPin17 50


//pins for stepper number 4
#define motorPin18 30
#define motorPin19 32
#define motorPin20 34
#define motorPin21 36

//pins for stepper number 5
#define motorPin22 22
#define motorPin24 24
#define motorPin26 26
#define motorPin28 28

//pins for stepper number 6
#define motorPin30 43
#define motorPin32 41
#define motorPin34 37
#define motorPin36 39

//pins for stepper number 7
#define motorPin38 47
#define motorPin40 51
#define motorPin42 49
#define motorPin44 53

//define pins for sensor 1
#define trigPin 13
#define echoPin 12

//define pins for sensor 2
#define trigPin2 40
#define echoPin2 38

//declare duration variables for sensor 1 and 2
long duration;
long duration2;

//declare distance variables for sensor 1 and 2
int distance;
int distance2;

//declare timer variable
int timer;

//initialize stepper motors
//stepper number 1
Stepper myStepper1(motorSteps, motorPin4,motorPin5,motorPin6,motorPin7);

//stepper number 2
Stepper myStepper2(motorSteps, motorPin8,motorPin9,motorPin10,motorPin11);

//stepper number 3
Stepper myStepper3(motorSteps, motorPin14,motorPin15,motorPin16,motorPin17);

//stepper number 4
Stepper myStepper4(motorSteps, motorPin18,motorPin19,motorPin20,motorPin21);

//stepper number 5
Stepper myStepper5(motorSteps, motorPin22,motorPin24,motorPin26,motorPin28);

//stepper number 6
Stepper myStepper6(motorSteps, motorPin30,motorPin32,motorPin34,motorPin36);

//stepper number 7
Stepper myStepper7(motorSteps, motorPin38,motorPin40,motorPin42,motorPin44);


void setup() {
  //set up speed of each stepper motor
  myStepper1.setSpeed(200);
  myStepper2.setSpeed(200);
  myStepper3.setSpeed(200);
  myStepper4.setSpeed(200);
  myStepper5.setSpeed(200);
  myStepper6.setSpeed(200);
  myStepper7.setSpeed(200);

//ultrasonic sensor code attributed to link below
//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

  // set trigpin Output
  pinMode(trigPin, OUTPUT);

   // set echoPin Input
   pinMode(echoPin, INPUT);

    // set trigpin2 Output
  pinMode(trigPin2, OUTPUT);

   // set echoPin2 Input
   pinMode(echoPin2, INPUT);
   
  //serial port to see information
   SerialUSB.begin(9600);
}

void loop() {

//------- Sensor related --------

  //clear trigPin
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  

  //reads echopin and gives back value in microseconds
 duration = pulseIn(echoPin, HIGH);

  
  
  //convert microseconds to distance for sensor 1
 distance= duration*0.034/2;

  

  //print distance on serial monitor
  SerialUSB.print("Distance1: ");
  SerialUSB.println(distance);

//We wrote the same code above for sensor 2 but our sensor 2
//ended up not working fast enought to take in values, therefore we took it out.
//We left the code in comments.

//-----Start of sensor 2 code implementation------
  /*clear trigPin2
  digitalWrite(trigPin2,LOW);
  delayMicroseconds(2);

  // Sets the trigPin2 on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  //reads echopin2 and gives back value in microseconds
  duration2 = pulseIn(echoPin2, HIGH);

  //convert microseconds to distance for sensor 2
  distance2= duration2*0.034/2;


  //print distance on serial monitor
  SerialUSB.print("Distance2: ");
  SerialUSB.println(distance2);*/

//-----End of sensor 2 code implementation------

//---------Stepper motor related code-----------
//motor code attributed to link below:
//https://www.arduino.cc/en/Tutorial/StepperSpeedControl

//always start by making stepper 6 shake(earthquake on island of montreal)
//when nothing is on the sensor, distance will always be greater than 200.
   if(distance > 200){
      myStepper6.step(1000);

     delay(100);
        myStepper6.step(-1000);
   }

//check if distance is less than 30
//if so, make motor 4 go up then down (wave effect)
  if(distance < 30){
    for(int s=0; s<1000; s++){
      myStepper4.step(-1);
     }
   //delay
  delay(100);
      for(int s=1000; s>=0; s--){
        myStepper4.step(1);
      }
  }


//if distance is less than 80 cm and greater than 30, make motors 1 and 3 go up and down one after the 
//other (wave effect)
  if(distance > 30 && distance < 80){
  //make motor 1 and 3 turn  number of steps
     myStepper1.step(1000);
     myStepper3.step(-1000);
      
  //delay
  delay(100);
  
  //make motor 1 and 3 go back down number of steps
    myStepper1.step(-1000);
    myStepper3.step(1000);     
  }



  //if distance1 is less than 150 and more than 80, make
  //stepper motors 2 and 7 go up and down at same time
  
 if(distance > 80 && distance < 150){

  for(int s=0; s<2000; s++){
      myStepper2.step(1);
      myStepper7.step(1);
     }
   //delay
  delay(100);
  
  for(int s=1000; s>=0; s--){
     myStepper2.step(-1);
     myStepper7.step(-1);
     }
  }

//stepper 5 not working therefore it couldn't be used

}
