#include <Base64.h>
#define MX (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (k[p&3^e]^z);

void xxtea_encrypt(char* v, char* k) {
    long n = strlen(v);
    unsigned long z=v[n-1], y=v[0], sum=0, e, /*DELTA=0x9e3779b9*/ DELTA = 7;
    long p, q ;
    
    /*Serial.print("z = ");
    Serial.println(z);
    Serial.print("y = ");
    Serial.println(y);*/
    
    if(n > 1) {
        q = 6 + 52/n;
        
        /*Serial.print("q = ");
        Serial.println(q);*/
        
        while (q-- > 0) {
            sum += DELTA;
            
           /* Serial.print("sum = ");
            Serial.println(sum);*/
            
            e = (sum >> 2) & 3;
   
            /*Serial.print("e = ");
            Serial.println(e);*/
            
            for (p=0; p<n-1; p++) {
              y = v[p+1];
              Serial.print("y = ");
              Serial.println(y);
              
              long mx = MX;
              Serial.print("mx = ");
              Serial.println(mx);
              
              Serial.print("v = ");
              Serial.println((long) v[p]);
              
              v[p] = v[p] + MX;
              
              Serial.print("vp = ");
              Serial.println((long) v[p]);
              
              z = v[p];
              Serial.print("z = ");
              Serial.println(z);
              
            }  
            
            y = v[0];
            z = v[n-1] += MX;
        }
    }
}

void xxtea_decrypt(char* v, char* k) {
    long n = strlen(v);
    unsigned long z=v[n-1], y=v[0], sum=0, e, /*DELTA=0x9e3779b9*/ DELTA = 7;
    
    Serial.println(v[n-1]);

    Serial.print("z: ");
    Serial.println(z);
    Serial.print("y: ");
    Serial.println(y);
    
    
    Serial.print("DELTA: ");
    Serial.println(DELTA);
    
    long p, q ;
    if(n > 1) {
        q = 6 + 52/n;
        Serial.print("q: ");
        Serial.println(q);
        
        sum = q*DELTA ;
        
        Serial.print("SUM: ");
        Serial.println(sum);
        while (sum != 0) {
            e = (sum >> 2) & 3;
            Serial.print("e = ");
            Serial.println(e);
            
            for (p=n-1; p>0; p--) {
              z = v[p-1];
              
              int mx = MX;
              Serial.print("mx = ");
              Serial.println(mx);
              
             y = v[p] -= MX;
            }
            
            z = v[n-1];
            y = v[0] -= MX;
            sum -= DELTA;
        }
    }
}


//VARIABILI
char * v = "Ciao!";

char o[12];

char k[] = "chiave";

void setup() {
  
  Serial.begin(9600);
  /*
  Serial.println("decode base64");
  base64_encode(output, input, length);
  */
  /*
  Serial.println("input text:");  
  Serial.println(v);
  Serial.println(strlen(v));
  
  Serial.println("encrypt xxtea");
  xxtea_encrypt(v, k);
  Serial.println(strlen(v));
  
  base64_encode(o, v, strlen(v));
  Serial.println(o);
  */
  
  //base64_decode(v, o, strlen(o));
  /*
  Serial.println("decrypt xxtea");
  xxtea_decrypt(v, k);
  Serial.println(v);
  Serial.println(strlen(v));
  */
  
  Serial.println("encrypt xxtea");
  xxtea_encrypt(v, k);
  //Serial.println(strlen(v));
  
  base64_encode(o, v, strlen(v));
  Serial.println(o);


}

void loop() {}



