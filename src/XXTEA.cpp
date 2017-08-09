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
XXTEA::XXTEA(char *key, size_t len) { //key must be length at maximun 16 characters

  //if the string key is larger of 16 charcters it will be truncated to 16
  if (len >= 16) {
    str2Long(_key, key, 16, 0);
  } else {
    str2Long(_key, key, len, 0);

    //if the converted key uses less than 4 long, the remanaining ones are set to 0
    for (int i = str2LongSize(len); i < 4; i++) {
      _key[i] = 0;
    }
  }


}

//metodo uasato per crittare un messaggio
size_t XXTEA::encrypt(char *str, size_t len, char *buffer, size_t buff_size) {

  //if the buffer size is too small
  if (buff_size < long2StrSize(str2LongSize(len) +1) +1) {
    return 0;
  }

  size_t size = str2LongSize(len) +1; //dimension of the long vector

  uint32_t v[size]; //instatiate the long vector with the right size

  str2Long(v, str, len, 1); //convert the string into long

  encryptArray(v, size); //chipher the vector

  return long2Str(buffer, v, size, 0); //vector to string

}

//metodo usato per decrittare il messaggio
size_t XXTEA::decrypt(char *str, size_t len, char *buffer, size_t buff_size) {

  if (buff_size < len -3) {
    return 0;
  }

  int size = str2LongSize(len);

  uint32_t v[size]; //creo array per contenere la stringa

  str2Long(v, str, len, 0); //converto la stringa in long

  decryptArray(v, size); //decritto il vettore

  return long2Str(buffer, v, size, 1);

}


//---PRIVATE INTERFACE---

//metod used to calculate powers
uint32_t XXTEA::pow(uint16_t base, uint8_t exp) {
  
  uint32_t result = 1;

  for (int i = 0; i < exp; i++) 
    result *= base;
  
  return result;
}

//metod that returns the dimension of the array to store the string converted into long
size_t XXTEA::str2LongSize(size_t len) {
  return len % 4 == 0 ? len/4 : len/4 + 1;
}

//method that returns the length of the string deconverted from the array of long
size_t XXTEA::long2StrSize(size_t len) {
  return len * 4;
}

//method that ciphers the given array of long using XXTEA algorithm
void XXTEA::encryptArray(uint32_t *v, size_t n) {

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
void XXTEA::decryptArray(uint32_t *v, size_t n) {

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
size_t XXTEA::long2Str(char *s, uint32_t *v, int l, int w) {

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
    
  	s[i] = (char) c;
    
  }

  if (w) {
    //error the len of the decrypted string is major of the maximum
    if (v[l-1] > length) {
      return 0;
    }

    length = v[l -1];
  }
  
	s[length] = '\0';

  return length;

}

//method that converts the string into long, it stores the converted string into the array of long passed
void XXTEA::str2Long(uint32_t* v, char* s, size_t len, uint8_t w) {

	for (int i = 0; i < len; i++) {
    int index = i / 4;
	  int esp = i % 4;

    uint32_t c;

    if ((int8_t) s[i] < 0) {
      c = (uint32_t) ((int8_t) s[i] + 256);
    } else {
      c = (uint32_t) s[i];
    }
	    
	  if (esp == 0) {
      v[index] = c;
	      
    } else {
      v[index] = v[index] + pow(256, esp) * c;
	  }

	}

  if (w) {
    v[(len -1) / 4 + 1] = len;
  }

}
