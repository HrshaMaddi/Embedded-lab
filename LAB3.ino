#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define button 2
#define receiver 13
int clockvise = 0;
int enablevalue=0;


#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include "IRremote.h"


int buttonpinold = 0, buttonpinnew = 0, secondpassed =0;
unsigned long myTime;



DS3231 clock;
RTCDateTime dt;
int i, checktime=0,ckecktimenew = 0;


LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'


void setup() 
{ irrecv.enableIRIn();
  lcd.begin(16, 2);
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);     


cli();//stop interrupts

//set timer4 interrupt at 1Hz
 TCCR4A = 0;// set entire TCCR1A register to 0
 TCCR4B = 0;// same for TCCR1B
 TCNT4  = 0;//initialize counter value to 0
 // set compare match register for 1hz increments
 OCR4A = 15624/1;// = (16*10^6) / (1*1024) - 1 (must be <65536)
 // turn on CTC mode
 TCCR4B |= (1 << WGM12);
 // Set CS12 and CS10 bits for 1024 prescaler
 TCCR4B |= (1 << CS12) | (1 << CS10);  
 // enable timer compare interrupt
 TIMSK4 |= (1 << OCIE4A);

sei();
}



ISR(TIMER4_COMPA_vect){
secondpassed = 1;
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//                                   REVERSE FUCNTION
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void reverse()
{ if(Serial.available())
{ buttonpinold = buttonpinnew;
  buttonpinnew = digitalRead(button);
  if(buttonpinnew != buttonpinold && buttonpinnew == 1)
  {
  
  }
}}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//                                   LOOP FUNCTION
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

void loop() 
{

if (irrecv.decode(&results)) 

  {
    translateIR();
    irrecv.resume(); 
 
  }

if(secondpassed ==1)
    { 
      secondpassed =0;
      dt = clock.getDateTime();
      lcd.setCursor(0, 1);
      lcd.print(dt.hour);
      lcd.print(":");
      lcd.print(dt.minute);
      lcd.print(":");
      lcd.print(dt.second);
      lcd.print("   "); 
    }

    
 if(Serial.available()!="")
{ delay(300);
  buttonpinold = buttonpinnew;
  buttonpinnew = digitalRead(button);
  if(buttonpinnew != buttonpinold && buttonpinnew == 1)
  {
     if(clockvise == 1)
     {lcd.setCursor(0, 0);
      lcd.print("CC");
      fan(HIGH, LOW, HIGH, enablevalue);
     }
     else
     {
      lcd.setCursor(0, 0);
      lcd.print("C ");
      fan(HIGH, HIGH, LOW, enablevalue);
     }
  }
}


}
  
  
  //-----------------------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------------------
  //                                   FAN SPEED AND DIRECTION
  //-----------------------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------------------
    
    
    void fan(char en, char dA, char dB,  int enspeed)
  {
  digitalWrite(ENABLE, en); // enable on
    digitalWrite(DIRA, dA);   //clockwise 
    digitalWrite(DIRB, dB);
    analogWrite(ENABLE, enspeed);
   }

  
  
  
  
  
  
  
  
  
  //-----------------------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------------------
  //                                   IR RECEIVER TRANSLATE FUNCTION
  //-----------------------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------------------
  void translateIR()
{

  switch(results.value)

  {
  case 0xFFA25D:
    lcd.setCursor(0, 0);
    lcd.print("    LAB3     ");
    break;
  case 0xFF30CF: 
    lcd.setCursor(0, 0);
    lcd.print("CC   OFF     ");
    fan(HIGH, LOW, HIGH, 0);
    clockvise = 0;
    enablevalue= 0;
    break;
  case 0xFF18E7: 
    lcd.setCursor(0, 0);
    lcd.print("CC   1/2     ");
    fan(HIGH, LOW, HIGH, 127);
    clockvise = 0;
    enablevalue= 127;
    break;
  case 0xFF7A85: 
    lcd.setCursor(0, 0);
    lcd.print("CC   3/4     ");
    fan(HIGH, LOW, HIGH, 190);
    clockvise = 0;
    enablevalue= 190;
    break;
  case 0xFF10EF: 
    lcd.setCursor(0, 0);
    lcd.print("CC   FULL    ");
    fan(HIGH, LOW, HIGH, 255);
    clockvise = 0;
    enablevalue= 255;
    break;
  case 0xFF38C7: 
  break;
  case 0xFF5AA5: 
    lcd.setCursor(0, 0);
    lcd.print("C    OFF     ");
    fan(HIGH, HIGH, LOW, 0);
    clockvise = 1;
    enablevalue= 0;
    break;
  case 0xFF42BD: 
    lcd.setCursor(0, 0);
    lcd.print("C    1/2     ");
    fan(HIGH, HIGH, LOW, 127);
    clockvise = 1;
    enablevalue= 127;
    break;
  case 0xFF4AB5: 
    lcd.setCursor(0, 0);
    lcd.print("C    3/4     ");
    fan(HIGH, HIGH, LOW, 190);
    clockvise = 1;
    enablevalue= 190;  
    break;
  case 0xFF52AD:
    lcd.setCursor(0, 0);
    lcd.print("C    FULL    "); 
    fan(HIGH, HIGH, LOW, 255);
    clockvise = 1;
    enablevalue= 255;    
    break;
  case 0xFFFFFFFF: 
    break;  

  default: 
    Serial.println(" INVALID INPUT ");

  }// End Case

  delay(100); // Do not get immediate repeat


}
  
 
