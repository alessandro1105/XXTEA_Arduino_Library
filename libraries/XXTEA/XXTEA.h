#ifndef _BASE64_H
#define _BASE64_H

class XXTEA {

	private:

		long* key; //variabile che conterrà la chiave

		long pow_long(long b, long e); //metodo usato per calcolare le potenze

		long strToLongSize(char* s); //restituisce la dimensione dell'array di long

		long longToStrSize(long* v, long l); //restituisce la dimensione della stringa

		void longToStr(char* s, long* v, long l); //converte array v di long in stringa

		void strToLong(long* v, char* s); //converte la stringa s in array di long

		long int32(long n); //fa in modo che non ci siano overflow durante le operazioni 

	public:
		XXTEA(char* k); //costruttore usato per settare la chiave

		void encrypt(char* s); //metodo uasato per crittare un messaggio

		void decrypt(char* s); //metodo usato per decrittare la stringa

};

#endif