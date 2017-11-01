#include <SPI.h>

int w_clk_pin = 13;
int fq_ud_pin = 9;
int d_out_pin = 11;
int reset_pin = 7;


void setup()
{
  // IO configuration
  pinMode(w_clk_pin, OUTPUT);
  pinMode(fq_ud_pin, OUTPUT);
  pinMode(d_out_pin, OUTPUT);
  pinMode(reset_pin, OUTPUT);
  
  // Reset AD9851
  delay(1);
  digitalWrite(reset_pin, HIGH);
  delay(1);
  digitalWrite(reset_pin, LOW);
  
  // Put the AD9851 in serial mode
  delay(1);
  digitalWrite(w_clk_pin, HIGH);
  delay(1);
  digitalWrite(w_clk_pin, LOW);
  delay(1);
  digitalWrite(fq_ud_pin, HIGH);
  delay(1);
  digitalWrite(fq_ud_pin, LOW);
  
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  
  unsigned char freqWordArray[4];
  unsigned char controlWord;
  unsigned long freqWord;
  double clockFrequency = 180000000;
  double targetFrequency = 2.95e6;
  
  double targetWord = targetFrequency*4.294967296e9/clockFrequency;
  
  freqWord = (unsigned long) targetWord;
  
  freqWordArray[0] = (unsigned char)(freqWord         & 0xFF);
  freqWordArray[1] = (unsigned char)((freqWord >> 8)  & 0xFF);
  freqWordArray[2] = (unsigned char)((freqWord >> 16) & 0xFF);
  freqWordArray[3] = (unsigned char)((freqWord >> 24) & 0xFF);
  controlWord      = 0x01;
  
  Serial.begin(9600);
 
  Serial.println("Target frequency:");
  Serial.println(targetFrequency);
  Serial.println(freqWordArray[0], HEX);
  Serial.println(freqWordArray[1], HEX);
  Serial.println(freqWordArray[2], HEX);
  Serial.println(freqWordArray[3], HEX);
  Serial.println(targetWord);
  
  SPI.transfer(freqWordArray[0]);
  SPI.transfer(freqWordArray[1]);
  SPI.transfer(freqWordArray[2]);
  SPI.transfer(freqWordArray[3]);
  SPI.transfer(controlWord);
  
  delay(1);
  digitalWrite(fq_ud_pin, HIGH);
  delay(1);
  digitalWrite(fq_ud_pin, LOW);

            
}

void loop()
{
 int i = 100000;
while(i > 0)
{
  i--;
}

}
