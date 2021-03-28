#include<Wire.h>
 char buzzervalue, sendbonus, sendpythonnew='\0', sendpythonold='x';
  const int buzzer = 5;
  const int SW_pin = 2;                                         // digital pin connected to switch output
  const int X_pin = 0;                                          // analog pin connected to X output
  const int Y_pin = 1;                                          // analog pin connected to Y output
  const int MPU_addr=0x68;                                      // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void setup()
{  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);                                             // PWR_MGMT_1 register
  Wire.write(0);                                                // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(SW_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  /* Serial.println(AcX);
  Serial.println(AcY);
  Serial.println(AcZ);
  Serial.println(GyX);
  Serial.println(GyY);
  Serial.println(GyZ);
  Serial.println(" "); 
  delay(200); */ 
  if(AcZ>25000)
  {
    sendbonus = 'z'; 
    Serial.write(sendbonus);
    delay(400);
  }
  if(analogRead(X_pin) < 200  || AcX > 6000)
  { sendpythonnew = 'a';
  }
  else if(analogRead(X_pin) > 800 || AcX < -6000)
  {
    sendpythonnew = 'd';
  }
 else if(analogRead(Y_pin) < 200 || AcY  < -5000)
  {
    sendpythonnew = 'w';
  }
  else if(analogRead(Y_pin) > 800 || AcY > 5000 )
  {
    sendpythonnew = 's';
  }
  if(sendpythonold != sendpythonnew)
  {
    Serial.write(sendpythonnew);
    delay(400);
    sendpythonold=sendpythonnew;
  }

  if(Serial.available())
  { buzzervalue = Serial.read();
  if(buzzervalue == 'x')
    {digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(buzzer, LOW);
  }}
  }
