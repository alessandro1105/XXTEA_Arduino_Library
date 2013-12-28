#include <XXTEA.h>

#include <Base64.h>

void setup() {
  
  Serial.begin(9600);
  
  XXTEA xxtea("0123456789012345");
  
  char* s  = "0123456789";
  char output[100];
  
  Serial.print(" ");
  
  xxtea.encrypt(s);
  //Serial.println(s);
  
  //base64_decode(output, s, strlen(s));
  //Serial.println(output);
  //Serial.println(strlen(s));
  
  xxtea.decrypt(s);
  
  Serial.println(s);
  
  
}

void loop() {}

