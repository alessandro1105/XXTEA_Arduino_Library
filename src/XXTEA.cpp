/*
   Copyright 2016 Alessandro Pasqualini
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
     http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
   @author         Alessandro Pasqualini <alessandro.pasqualini.1105@gmail.com>
   @url            https://github.com/alessandro1105
*/

#include "XXTEA.h"
#include <string.h>
#include <Arduino.h>


//---PUBLIC INTERFACE---

//costructor of the class
XXTEA::XXTEA(char *key) { //key must be length at maximun 16 characters

  //conversion of the given key to array of long
	str2Long(_key, key, 0);

  //if the converted key uses less than 4 long, the remanaining ones are set to 0
  for (int i = str2LongSize(key); i < 4; i++) {
    _key[i] = 0;
  }

}

//metodo uasato per crittare un messaggio
int XXTEA::encrypt(char *str) {

  int size = str2LongSize(str) +1; //dimension of the long vector

  uint32_t v[size]; //instatiate the long vector with the right size

  str2Long(v, str, 1); //convert the string into long

  encryptArray(v, size); //chipher the vector

  long2Str(str, v, size, 0); //vector to string

}

//metodo usato per decrittare il messaggio
int XXTEA::decrypt(char *str) {

  int size = str2LongSize(str);

  uint32_t v[size]; //creo array per contenere la stringa

  str2Long(v, str, 0); //converto la stringa in long

  decryptArray(v, size); //decritto il vettore

  long2Str(str, v, size, 1);

}


//---PRIVATE INTERFACE---

//metod used to calculate powers
uint32_t XXTEA::pow(uint32_t base, uint32_t exp) {
  
  uint32_t result = 1;

  for (int i = 0; i < exp; i++) 
    result *= base;
  
  return result;
}

//metod that returns the dimension of the array to store the string converted into long
uint32_t XXTEA::str2LongSize(char *str) {
  return strlen(str) % 4 == 0 ? strlen(str) / 4 : strlen(str) / 4 + 1;
}

//method that returns the length of the string deconverted from the array of long
uint32_t XXTEA::long2StrSize(int len) {
  return len * 4;
}

//method that ciphers the given array of long using XXTEA algorithm
void XXTEA::encryptArray(uint32_t *v, int n) {

  uint32_t y, z, sum;
  unsigned p, rounds, e;

  rounds = 6 + 52/n;
  sum = 0;
  z = v[n-1];
  do {
    sum += DELTA;
    e = (sum >> 2) & 3;
    for (p=0; p<n-1; p++) {
      y = v[p+1]; 
      z = v[p] += MX;
    }
    y = v[0];
    z = v[n-1] += MX;
  } while (--rounds);

}

//method that deciphers the given array of long using XXTEA algorithm
void XXTEA::decryptArray(uint32_t *v, int n) {

  uint32_t y, z, sum;
  unsigned p, rounds, e;

  rounds = 6 + 52/n;
  sum = rounds*DELTA;
  y = v[0];
  do {
    e = (sum >> 2) & 3;
    for (p=n-1; p>0; p--) {
      z = v[p-1];
      y = v[p] -= MX;
    }
    z = v[n-1];
    y = v[0] -= MX;
    sum -= DELTA;
  } while (--rounds);

}

//method that converts the array of long into a string, it stores the string into the array of long passed
void XXTEA::long2Str(char *s, uint32_t *v, int l, int w) {

  int length = long2StrSize(l);

  for (int i = 0; i < length; i++) {
    int index = i / 4;
    int esp = i % 4;

    uint32_t c;

    if (esp +1 == 4) {
      c = v[index];

    } else {
      	c = v[index] - (v[index] / pow(256, esp +1) * pow(256, esp +1));
    }
    
    if (esp > 0) {
    		c = c / pow(256, esp); 
  	}

    //c is negative
    if (c < 0) {
      c = 0xFFFFFFFF - c;
      c = 0xFF - c;

      if (esp != 0) { //if is not the first character
        c = c -1;
      }
    }
    
  	s[i] = (char) c;
    
  }

  if (w) {
    length = v[l -1];
  }
  
	s[length] = '\0';

}

//method that converts the string into long, it stores the converted string into the array of long passed
void XXTEA::str2Long(uint32_t *v, char *s, int w) {
	
  int size = strlen(s);

	for (int i = 0; i < size; i++) {
    int index = i / 4;
	  int esp = i % 4;

    uint32_t c = (uint32_t) s[i];

    //c is negative
    if (c < 0) {
      c = 0xFFFFFFFF - c;
      c = 0xFF - c;
    }
	    
	  if (esp == 0) {
      v[index] = c;
	      
    } else {
      v[index] = v[index] + pow(256, esp) * c;
	  }

	}

  if (w) {
    v[(size -1) / 4 + 1] = size;
  }

}
