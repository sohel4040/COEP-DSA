#include "Encryption/cipher.h"
#include "nosql.h"
#include<stdlib.h>
#include<stdio.h>
#include "globals/globals.h"

char * test(char * str){
    char * s = Encrypt(str);
    printf("Encrypted -> '%s'\n\n",s); 
    return(Decrypt(s));
}

int main(){
    noSQLMenu(); 
    // char * encrypt = dataEncrypt("Hello Sohel");
    // char * Decrypt = dataDecrypt("%MKF:<D#bR[b47@3M");
    // printf("%s\n",Decrypt);
return 0;
}
