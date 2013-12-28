#include "XXTEA.h"
#include <string.h>

//costruttore usato per settare la chiave
XXTEA::XXTEA(char* k) { //k max 16 caratteri

	this->strToLong(this->key, k, 0); //converto la chiave in array di interi

  for (int i = this->strToLongSize(k); i < 4; i++) {
    this->key[i] = 0;
  }

}

//metodo usato per calcolare le potenze
long XXTEA::pow_long(long b, long e) {

	long r = 1;
 	for (int i = 0; i < e; i++) 
    r *= b;
  
  return r;
}

//restituisce la dimensione dell'array di long
long XXTEA::strToLongSize(char* s) {

	int length = strlen(s) / 4;
  if (strlen(s) % 4 != 0) {
  		length++;
	}
  
  	return length;
}

//restituisce la dimensione della stringa
long XXTEA::longToStrSize(long* v, int l) {

  return l * 4;

}

//converte array v di long in stringa
void XXTEA::longToStr(char* s, long* v, int l, int w) {

  int length = longToStrSize(v, l);

  for (int i = 0; i < length; i++) {
    int index = i / 4;
    int esp = i % 4;

    long c;

    if (esp +1 == 4) {
      c = v[index];

    } else {
      	c = v[index] - (v[index] / pow_long(256, esp +1) * pow_long(256, esp +1));
    }
    
    if (esp > 0) {
    		c = c / pow_long(256, esp); 
  	}

    //PARTE CRITICA
    if (c < 0) { //se negativo "positivizzo"
      c = 0xFFFFFFFF - c;
      c = 0xFF - c;

      if (esp != 0) { // se non è il primo carattere
        c = c -1;
      }
    }
    //FINE PARTE CRITICA
    
  	s[i] = (char) c;
    
  }

  if (w) {
    length = v[l -1];
  }
  
	s[length] = '\0';

}

//converte la stringa s in array di long
void XXTEA::strToLong(long* v, char* s, int w) {
	
  int size = strlen(s);

	for (int i = 0; i < size; i++) {
    int index = i / 4;
	  int esp = i % 4;

    long c = (long) s[i];

    //PARTE CRITICA
    if (c < 0) { //se negativo "positivizzo"
      c = 0xFFFFFFFF - c;
      c = 0xFF - c;
    }
    //FINE PARTE CRITICA
	    
	  if (esp == 0) {
      v[index] = c;
	      
    } else {
      v[index] = v[index] + pow_long(256, esp) * c;
	  }

	}

  if (w) {
    v[(size -1) / 4 + 1] = size;
  }

}

//critta array di long
void XXTEA::encryptArray(long* v, int l) {

  long z = v[l -1];
  long y = v[0];

  long q = 6 + 52 / l;
  long sum = 0;

  long p;

  while (q-- > 0) {
    sum += DELTA;
    long e = sum >> 2 & 3;

    for (p = 0; p < l -1; p++) {
      y = v[p +1];
      long mx = ((z >> 5 & 0x07FFFFFF) ^ y << 2) + ((y >> 3 & 0x1FFFFFFF) ^ z << 4) ^ ((sum ^ y) + (this->key[p & 3 ^ e] ^ z));
      z = v[p] = v[p] + mx;
    }

    y = v[0];
    long mx = ((z >> 5 & 0x07FFFFFF) ^ y << 2) + ((y >> 3 & 0x1FFFFFFF) ^ z << 4) ^ ((sum ^ y) + (this->key[p & 3 ^ e] ^ z));
    z = v[l -1] = v[l -1] + mx;

  }

}

//decritta array di long
void XXTEA::decryptArray(long* v, int l) {

  long z = v[l -1];
  long y = v[0];

  long q = 6 + 52 / l;
  long sum = q * DELTA;

  long p;

  while (sum != 0) {
    long e = sum >> 2 & 3;

    for (p = l -1; p > 0; p--) {
      z = v[p - 1];

      long mx1 = ((z >> 5 & 0x07FFFFFF) ^ y << 2) + ((y >> 3 & 0x1FFFFFFF) ^ z << 4);
      long mx2 = (sum ^ y) + (this->key[p & 3 ^ e] ^ z);
      long mx = mx1^ mx2;

      y = v[p] -= mx;
    }

    z = v[l -1];

    long mx1 = ((z >> 5 & 0x07FFFFFF) ^ y << 2) + ((y >> 3 & 0x1FFFFFFF) ^ z << 4);
    long mx2 = (sum ^ y) + (this->key[p & 3 ^ e] ^ z);
    long mx = mx1^ mx2;

    y = v[0] -= mx;
    sum -= DELTA;

  }

}

//metodi pubblici

//metodo uasato per crittare un messaggio
void XXTEA::encrypt(char* s) {

  int size = this->strToLongSize(s) +1;

  long v[size]; //creo array per contenere la stringa

  this->strToLong(v, s, 1); //converto la stringa in long

  this->encryptArray(v, size); //critto il vettore

  this->longToStr(s, v, size, 0);

}

//metodo usato per decrittare il messaggio
void XXTEA::decrypt(char* s) {

  int size = this->strToLongSize(s);

  long v[size]; //creo array per contenere la stringa

  this->strToLong(v, s, 0); //converto la stringa in long

  this->decryptArray(v, size); //decritto il vettore

  this->longToStr(s, v, size, 1);

}
