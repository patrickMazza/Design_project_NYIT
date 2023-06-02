#include <Wire.h>

int LDC = 0x2A; //create the LDC object, when the ADDR pin is high (which it is for us) the I2C address is 0x2A

/* Most Significant bit and Least Significant bits for each channel, beginning with only two channels, add the others later. Also initial0,1 is for calibration/*
 *  
 */
int CH0MSB = 0x00;
int CH0LSB = 0x01;
int CH1MSB = 0x02;
int CH1LSB = 0x03;
int CH2MSB = 0x04;
int CH2LSB = 0x05;
long initial0 = 0;
long initial1 = 0;
long initial2 = 0;
//ORDER: A3, A0, A1, A2

//starts from MSB to LSB. First three digits presents D7, D6, D5.
byte controlPins[] = {B01100000,
              B00000000,
               B00100000,
               B01000000,
                   };

unsigned long readChannel0() {
  unsigned long val = 0;
  word c = 0; //a word stores a 16-bit unsigned number
  word d = 0;
  c = readValue(LDC, CH0MSB);
  d = readValue(LDC, CH0LSB);
  val = c;
  val <<= 16;
  val += d;
  return val;
}

unsigned long readChannel1(){
  unsigned long val = 0;
  word c = 0; //a word stores a 16-bit unsigned number
  word d = 0;
  c = readValue(LDC, CH1MSB);
  d = readValue(LDC, CH1LSB);
  val = c;
  val <<= 16;
  val += d;
  return val;
}

unsigned long readChannel2(){
  unsigned long val = 0;
  word c = 0; //a word stores a 16-bit unsigned number
  word d = 0;
  c = readValue(LDC, CH2MSB);
  d = readValue(LDC, CH2LSB);
  val = c;
  val <<= 16;
  val += d;
  return val;
}

void Calibrate(){

  initial2 = readChannel2();
}

word readValue (int LDC, int reg){
  int a = 0;
  int b = 0;
  word value = 0;
  Wire.beginTransmission(LDC);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(LDC, 2);
  while (Wire.available()){
    a = Wire.read();
    b = Wire.read();
  }
  value = a;
  value <<= 8;
  value += b;
  return value;
}

void writeConfig(int LDC, int reg, int MSB, int LSB) {
  Wire.beginTransmission(LDC);
  Wire.write(reg);
  Wire.write(MSB);
  Wire.write(LSB);
  Wire.endTransmission();
}

void Configuration_CH2() {
  writeConfig(LDC, 0x1A, 0x34, 0x01);//CONFIG 0x34, 0x41 Device Sleep //TUNED
  writeConfig(LDC, 0x1B, 0x82, 0x0D);//MUX_CONFIG // TUNED - DEGLITCH 10MHz
  writeConfig(LDC, 0x20, 0x0c, 0x00);//DRIVE_CURRENT_CH0 @0 - 16 uA
  writeConfig(LDC, 0x1A, 0x14, 0x01);//CONFIG 0x14, 0x41 Device Active //TUNED
  delay(250);
  Calibrate();
}

void Configuration(){
  writeConfig(LDC, 0x14, 0x10, 0x02);//CLOCK_DIVIDERS_CH0
  writeConfig(LDC, 0x1E, 0x08, 0x00);//DRIVE_CURRENT_CH0
  writeConfig(LDC, 0x10, 0x06, 0x10);//SETTLECOUNT_CH0
  writeConfig(LDC, 0x08, 0xFF, 0xFF);//RCOUNT_CH0
  writeConfig(LDC, 0x15, 0x10, 0x02);//CLOCK_DIVIDERS_CH1
  writeConfig(LDC, 0x1F, 0x08, 0x00);//DRIVE_CURRENT_CH1
  writeConfig(LDC, 0x11, 0x06, 0x10);//SETTLECOUNT_CH1
  writeConfig(LDC, 0x09, 0xFF, 0xFF);//RCOUNT_CH1
 
  writeConfig(LDC, 0x16, 0x10, 0x02);//CLOCK_DIVIDERS_CH2
  writeConfig(LDC, 0x20, 0x08, 0x00);//DRIVE_CURRENT_CH2
  writeConfig(LDC, 0x12, 0x06, 0x10);//SETTLECOUNT_CH2
  writeConfig(LDC, 0x0A, 0xFF, 0xFF);//RCOUNT_CH2
  writeConfig(LDC, 0x19, 0x00, 0x00);//ERROR_CONFIG
  //writeConfig(LDC, 0x1B, 0x82, 0x0C);//MUX_CONFIG: initialize at 3.3MHz
  }

void setPin(int outputPin)
// function to select pin on 74HC4067
{
  PORTD = controlPins[outputPin];
}

 int j;
 int i;
 
void setup() {
  i = 0;
  j = 0;
  Wire.begin();
  Serial.begin(9600);
  Configuration();
  delay(250);
  Calibrate();
  DDRD = B11111111;

    // A1
    /*
   digitalWrite(5, HIGH);
   digitalWrite(6,LOW);
   digitalWrite(7,LOW);
   */
   
  /*
  pinMode(8,OUPUT);
  pinMode(9,OUPUT);
  pinMode(10,OUPUT);
  pinMode(11,OUPUT);
  pinMode(12,OUPUT);
  digitalWrite(8,LOW);//E1
  digitalWrite(9,HIGH);//E2
  digitalWrite(10,LOW);//S2
  digitalWrite(11,LOW);//S1
  
  digitalWrite(12,LOW);//S0
*/
}


void loop() {
     
  //unsigned long data0 = readChannel0();
   

    for(i = 0; i < 4; i++){
     
      unsigned long data2 = readChannel2();
      setPin(i);
      delay(1750);
     // unsigned long data2 = readChannel2();
      Serial.println(data2);
      //delay(50000);
      
    }
   
   
   /*
   for(int i = 0; i < 1; i++){
      setPin(i);
      unsigned long data2 = readChannel2();
      Serial.println(data2);
      delay(2000);
    }
   
   */

   
     unsigned long data2 = readChannel2();
  

   
    Serial.println(data2);
    delay(2500);

}
