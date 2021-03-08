//-----------------------------------------------------------------------------------------------------------------
                   // Declaring global vairables for pins connected to Arduino
//-----------------------------------------------------------------------------------------------------------------



                   // Declaring global vairables for pins connected to Arduino 
const int digitPins[4] = {4,5,6,7};                //4 common anode pins of the display
const int clockPin = 10;                           //74HC595 Pin 11 
const int latchPin = 9;                            //74HC595 Pin 12
const int dataPin = 8;                             //74HC595 Pin 14
const int red =  3;                                // RED LED pin 3
const int yellow =  2;                             // RED LED Pin 2
const int green =  1;                              // RED LED Pin 1
const int buzzer = 11;                             // Active Buzzer Pin 11
const int startpin = 12;                           // Startpin(to start R G B loop) pin 12
int buttonpin = 0;
unsigned char digit[] =                            //seven segment digits in bits (0 to F)
{
 0x3f,0x06,0x5b,0x4f,
 0x66,0x6d,0x7d,0x07,
 0x7f,0x6f,0x77,0x7c,
 0x39,0x5e,0x79,0x71
};



//-----------------------------------------------------------------------------------------------------------------
                               // Setting all the pins as INPUT/OUTPUT
//-----------------------------------------------------------------------------------------------------------------
void setup(){                
  for(int i=0;i<4;i++)
  {
    pinMode(digitPins[i],OUTPUT);    // defining enable pins for digits on 7 segment display as output
  }
 
  pinMode(latchPin, OUTPUT);        // defining Latchpin as output
  pinMode(clockPin, OUTPUT);        // defining clockpin as output
  pinMode(dataPin, OUTPUT);         // defining datapin as output
  pinMode(red, OUTPUT);            // defining RED as output
  pinMode(yellow, OUTPUT);         // defining YELLOW as output
  pinMode(green, OUTPUT);          // defining GREEN as output
  pinMode(buzzer, OUTPUT);         // defining buzzer as output
  pinMode(startpin, INPUT);        // defining Startpin as input
}




//-----------------------------------------------------------------------------------------------------------------
                                //writes the time on 7 SEGMENT display
//-----------------------------------------------------------------------------------------------------------------
void updateDisp(unsigned char countdown){
 if(countdown>9)
  {
      for(int p=0;p<120;p++){
    digitalWrite(digitPins[0], HIGH);
    digitalWrite(digitPins[1], HIGH);
    digitalWrite(digitPins[2], HIGH);
    digitalWrite(digitPins[3], LOW);

  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, MSBFIRST,digit[countdown-10]);
  delay(4);
  digitalWrite(latchPin, HIGH);


  
  digitalWrite(digitPins[0], HIGH);
    digitalWrite(digitPins[1], HIGH);
    digitalWrite(digitPins[2], LOW);
    digitalWrite(digitPins[3], HIGH);

  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, MSBFIRST,digit[1]);
  delay(4);
  digitalWrite(latchPin, HIGH);
    }}
    else
  {
      for(int p=0;p<120;p++){
    digitalWrite(digitPins[0], HIGH);
    digitalWrite(digitPins[1], HIGH);
    digitalWrite(digitPins[2], HIGH);
    digitalWrite(digitPins[3], LOW);

  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, MSBFIRST,digit[countdown]);
  delay(4);
  digitalWrite(latchPin, HIGH);


  
  digitalWrite(digitPins[0], HIGH);
    digitalWrite(digitPins[1], HIGH);
    digitalWrite(digitPins[2], LOW);
    digitalWrite(digitPins[3], HIGH);

  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, MSBFIRST,digit[0]);
  delay(4);
  digitalWrite(latchPin, HIGH);
    }
  
  }
  
}
//-----------------------------------------------------------------------------------------------------------------
                              // CODE For Traffic Lights and the Buzzer
//-----------------------------------------------------------------------------------------------------------------

void trafficlights()
{

 
for(int countdown=15; countdown >=0;countdown--)
  {digitalWrite(red, HIGH);
  if(countdown<=3)
  {digitalWrite(buzzer, HIGH);}
    updateDisp(countdown);
  }digitalWrite(red, LOW);
  digitalWrite(buzzer, LOW);

for(int countdown=15; countdown >=0;countdown--)
  {digitalWrite(green, HIGH);
   if(countdown<=3)
  {digitalWrite(buzzer, HIGH);}
    updateDisp(countdown);
  }digitalWrite(green, LOW);
  digitalWrite(buzzer, LOW);
  
for(int countdown= 3; countdown >=0;countdown--)
  {digitalWrite(yellow, HIGH);
   if(countdown<=3)
  {digitalWrite(buzzer, HIGH);}
    updateDisp(countdown);
  }digitalWrite(yellow, LOW);
  digitalWrite(buzzer, LOW);




trafficlights();
}

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void button()
{
  buttonpin = digitalRead(startpin);
  if(buttonpin)
  {
    digitalWrite(red, LOW);
    trafficlights();
  }
}
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void loop()
{  
digitalWrite(red, HIGH);
button();
}
