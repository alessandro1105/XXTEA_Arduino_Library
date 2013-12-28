#include <Base64.h>

char * input = "ciao";
char output[100];


void setup(){
  Serial.begin(9600);
  
  base64_encode(output, input, strlen(input));
  
  Serial.println(output);
  
  Serial.println("Test");

}

void loop() {}

