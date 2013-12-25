/*
 * =====================================================================================
 *
 *       Filename:  xxtea.c
 *
 *    Description:  Xxtea algorithm
 *
 *        Version:  1.0
 *        Created:  02/05/10 10:06:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chancey <chanceycn@gmail.com>
 *
 * =====================================================================================
 */

#define MX (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (k[p&3^e]^z);

#include <stdio.h>
#include <string.h>

void xxtea_encrypt(char* v, char* k) {
    long n = strlen(v);
    unsigned long z=v[n-1], y=v[0], sum=0, e, DELTA=0x9e3779b9;
    long p, q ;
    if(n > 1) {
        q = 6 + 52/n;
        while (q-- > 0) {
            sum += DELTA;
            e = (sum >> 2) & 3;
            for (p=0; p<n-1; p++) y = v[p+1], z = v[p] += MX;
            y = v[0];
            z = v[n-1] += MX;
        }
    }
}

void xxtea_decrypt(char* v, char* k) {
    long n = strlen(v);
    unsigned long z=v[n-1], y=v[0], sum=0, e, DELTA=0x9e3779b9;
    long p, q ;
    if(n > 1) {
        q = 6 + 52/n;
        sum = q*DELTA ;
        while (sum != 0) {
            e = (sum >> 2) & 3;
            for (p=n-1; p>0; p--) z = v[p-1], y = v[p] -= MX;
            z = v[n-1];
            y = v[0] -= MX;
            sum -= DELTA;
        }
    }
}

int main()
{
    char v[] = "date|cookies|ASDSADAS";
    char k[] = "2234567890123456";   

    xxtea_encrypt(v, k);
    printf("%s\n\n", v);

    xxtea_decrypt(v, k);
    printf("%s\n", v);

    return 0;
}
