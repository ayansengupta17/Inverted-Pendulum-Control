/* 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Reading decoder HCTL-2022 to count pulses from
an encoder using Arduino Mega 2560
Written by Ayan Sengupta
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Arduino Pin       HCTL-2022 function
------------------------------------
DIG 40            /RST (active low)
DIG 38            SEL1
DIG 39            SEL2
DIG 22->29        Data pins D0->D7
DIG 30->37        Data pins D0->D7 for 2nd Decoder
+5V               VDD
GND               VSS
from encoder      CHA
from encoder      CHB
not connected     INDEX
not connected     U/D
not connected     TEST 
PIN12   CLK
8   
9
*/
volatile long countData = 0;
volatile long count_en1 = 0;
volatile long count_en2 = 0;// 32-bit int (signed?) the count represents absolute position
long int en1,en2;
int t1,t2,dt;
float prev_theta,prev_alpha;


void setup() {
  t1=0;
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);
  pinMode(40, OUTPUT);
  digitalWrite(40, LOW); // /RST resets the internal counter between runs
  delay(10);
  digitalWrite(40, HIGH); // Stay high for rest of the run
  TCCR1B=0x01; //set timer 1 frequency to 31kHz
  analogWrite(12,128);

  
  // Set all pins in PORTA (digital pins 22->38 on the Mega) as input pins
  for(int i = 22; i<38; i++) {
    pinMode(i, INPUT);
  }

  
  for(int j = 8 ;j<10; j++) {
    pinMode(j, OUTPUT);
    digitalWrite(j, LOW);
    
  }

}
byte getMSBA(){
  byte MSBold = PINA;       // read datapins D0->D7 and store in MSBold
  byte MSBnew = PINA;       // read again immediatly after to assure stable data
  if (MSBnew == MSBold){ 
    byte MSBresult = MSBnew;
    return MSBresult;  
  }
  else getMSBA();
}
byte getMSBC(){
  byte MSBold = PINC;       // read datapins D0->D7 and store in MSBold
  byte MSBnew = PINC;       // read again immediatly after to assure stable data
  if (MSBnew == MSBold){ 
    byte MSBresult = MSBnew;
    return MSBresult;  
  }
  else getMSBC();
}

byte getLSBA(){
/*Get stable data for the least significant byte of countData*/
  byte LSBold = PINA;       // read datapins D0->D7 and store in LSBold
  byte LSBnew = PINA;       // read again immediatly after to assure stable data
  if (LSBnew == LSBold){  
    byte LSBresult = LSBnew;
    return LSBresult;  
  }
  else getLSBA();
}
byte getLSBC(){
/*Get stable data for the least significant byte of countData*/
  byte LSBold = PINC;       // read datapins D0->D7 and store in LSBold
  byte LSBnew = PINC;       // read again immediatly after to assure stable data
  if (LSBnew == LSBold){  
    byte LSBresult = LSBnew;
    return LSBresult;  
  }
  else getLSBC();
}


long mergeFunc(byte MSBresult,  byte LSBresult){
  long tempVar = 0;
  tempVar |= ((long) MSBresult << 8) |((long) LSBresult << 0);
  countData = tempVar;
  return countData;
}
void loop() {
  
  digitalWrite(38, LOW);
  digitalWrite(39, LOW); // SEL1 = 0 and SEL2 = 1
  
 
  byte enc1_MSB = getMSBA();
  byte enc2_MSB = getMSBC();
  
  digitalWrite(38, HIGH);
  digitalWrite(39, LOW); 
  
  byte enc1_LSB = getLSBA();
  byte enc2_LSB = getLSBC();
  
  count_en1 = int(mergeFunc(enc1_MSB,enc1_LSB));
  count_en2 = int(mergeFunc(enc2_MSB,enc2_LSB));
  
  en1 = 0.18*count_en1;
  en2 = 0.18*count_en2;
  t2=millis();
  
  dt=t2-t1;
  
  float theta=en1;  
  float alpha=en2;  
  float d_theta=((theta-prev_theta)/dt)*1000;
  float d_alpha=((alpha-prev_alpha)/dt)*1000;
  /*float k1 = -4.4;
  float k2 = 130;
  float k3=  -4.4;
  float k4= 17.44;*/

// better 
   float k1 = 9.4;
  float k2 = 98.5;
  float k3=  -4.1;
  float k4= 13;
  
  /*
  float k1 = -9.4; //q = 90,5,4,1
  float k2 = 115;
  float k3=  -4.9;
  float k4= 15.36;
  */
  
  float u = k1*theta + k2*alpha + k3*d_theta +k4*d_alpha;
  u = 0.3*u;
  if (u>0){
    if (u>255){
      u =255;
    }
  analogWrite(8,u);
  analogWrite(9,0);
  }
  if (u<0){
    if(u<-255){
      u = -255;   
    }
  analogWrite(8,0);
  analogWrite(9,abs(u));
  }
prev_theta=theta;
prev_alpha=alpha;
t1=t2;
delay(20);
  Serial.print(en1);
  Serial.print("\t");
  Serial.print(en2);
  Serial.print("\t");
  Serial.println(t2);
  
  }
  
 
