#ifndef _XXTEA_H
#define _XXTEA_H

class XXTEA {

	private:

		static const unsigned long DELTA = 0x9E3779B9;

		long key[4]; //variabile che conterrà la chiave

		long pow_long(long b, long e); //metodo usato per calcolare le potenze

		long strToLongSize(char* s); //restituisce la dimensione dell'array di long

		long longToStrSize(long* v, int l); //restituisce la dimensione della stringa

		void longToStr(char* s, long* v, int l, int w); //converte array v di long in stringa

		void strToLong(long* v, char* s, int w); //converte la stringa s in array di long

		void encryptArray(long* v, int l); //critta array di long

		void decryptArray(long* v, int l); //decritta array di long

	public:
		XXTEA(char* k); //costruttore usato per settare la chiave

		void encrypt(char* s); //metodo uasato per crittare un messaggio

		void decrypt(char* s); //metodo usato per decrittare il messaggio

};

#endif