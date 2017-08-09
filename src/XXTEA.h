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

#ifndef XXTEA_H
#define XXTEA_H

#include <Arduino.h>

//delta neded to XXTEA algorithm
#define DELTA 0x9E3779B9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (_key[(p&3)^e] ^ z)))


//class XXTEA
class XXTEA {

	public:

		//constructor of the class, it requires the key used to cipher the data
		XXTEA(char *key, size_t len);

		//method that ciphers the message given
		size_t encrypt(char *str, size_t len, char *buffer, size_t buff_size);

		//mathod that decipher the message given
		size_t decrypt(char *str, size_t len, char *buffer, size_t buff_size);


	private:

		//metod used to calculate powers
		uint32_t pow(uint16_t base, uint8_t exp);

		//method that ciphers the given array of long using XXTEA algorithm
		void encryptArray(uint32_t *v, size_t n);

		//method that deciphers the given array of long using XXTEA algorithm
		void decryptArray(uint32_t *v, size_t n);

		//metod that returns the dimension of the array to store the string converted into long
		size_t str2LongSize(size_t len);

		//method that returns the length of the string deconverted from the array of long
		size_t long2StrSize(size_t len);

		//method that converts the array of long into a string, it stores the string into the array of long passed
		size_t long2Str(char* s, uint32_t* v, int l, int w);

		//method that converts the string into long, it stores the converted string into the array of long passed
		void str2Long(uint32_t* v, char* s, size_t len, uint8_t w); //converte la stringa s in array di long

		//key used to cipher/decipher
		uint32_t _key[4];

};

#endif