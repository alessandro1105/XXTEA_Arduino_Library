#include "XXTEA.h"
#include <string.h>

//costruttore usato per settare la chiave
XXTEA::XXTEA(char* k) {

	long keyLong[this->strToLongSize(k)]; //creo un array di long per contenere la chiave

	this->strToLong(keyLong, k); //converto la chiave in array di interi

	this->key = keyLong; //puntatore classe all'array di long della chiave

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
long XXTEA::longToStrSize(long* v, long l) {

	long length = (l - 1) * 4;
  
  	if (v[l - 1] / pow_long(256, 3) > 0) {
    	length += 4; 

  	} else if (v[l - 1] / pow_long(256, 2) > 0) {
    	length += 3; 

 	} else if (v[l - 1] / pow_long(256, 1) > 0) {
    	length += 2; 

  	} else {
    	length += 1;
  	}
  
	return length;
}

//converte array v di long in stringa
void XXTEA::longToStr(char* s, long* v, long l) {

	int length = longToStrSize(v, l);
  
  	for (int i = 0; i < length -1; i++) {
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
    
    	s[i] = (char) c;
    
  	}
  
  	s[length] = '\0';
}

//converte la stringa s in array di long
void XXTEA::strToLong(long* v, char* s) {
	
	for (int i = 0; i < strlen(s); i++) {
	    int index = i / 4;
	    int esp = i % 4;
	    
	    if (esp == 0) {
	     	v[index] = (long) s[i];
	      
	    } else {
	     	v[index] = v[index] + pow_long(256, esp) * ((long) s[i]);
	    }
  
	}
}

//fa in modo che non ci siano overflow durante le operazioni 
long XXTEA::int32(long n) {

	while (n >= 2147483648) n -= 4294967296;
    while (n <= -2147483649) n += 4294967296;
    
    return n;
}