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

//delta neded to XXTEA algorithm
#define DELTA 0x9E3779B9


//class XXTEA
class XXTEA {

	public:

		//constructor of the class, it requires the key used to cipher the data
		XXTEA(char *key);

		//method that ciphers the message given
		int encrypt(char *str);

		//mathod that decipher the message given
		int decrypt(char *str);


	private:

		//metod used to calculate powers
		long pow(long base, long exp);

		//method that ciphers the given array of long using XXTEA algorithm
		void encryptArray(long *v, int l);

		//method that deciphers the given array of long using XXTEA algorithm
		void decryptArray(long *v, int l);

		//metod that returns the dimension of the array to store the string converted into long
		long str2LongSize(char *str);

		//method that returns the length of the string deconverted from the array of long
		long long2StrSize(int len);

		//method that converts the array of long into a string, it stores the string into the array of long passed
		void long2Str(char* s, long* v, int l, int w);

		//method that converts the string into long, it stores the converted string into the array of long passed
		void str2Long(long* v, char* s, int w); //converte la stringa s in array di long

		//key used to cipher/decipher
		long _key[4];

};

#endif