#include "cipher.h"
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h> // for implementing getch
#include <termios.h>


#define MODULO 122

typedef struct Key{
    char * key;
    int length;
}Key;

void initKey(Key * key, int length){
    key->key = (char *) malloc(sizeof(char) * length); 
    key->length = length;
    return;
}

Key * getPolyAlphabeticKey(Key * key){
    FILE * fptr = fopen(".encryptKey","r"); 

    // Moving pointer to end of file
    fseek(fptr, 0L, SEEK_END);
    int length = ftell(fptr);
    initKey(key,length);    
    fseek(fptr, 0L, SEEK_SET);
    fscanf(fptr,"%s",key->key);
    fclose(fptr);
    return key;
}

char * Encrypt(char * str){
    
    int length = getLength(str);
    Key key;
    getPolyAlphabeticKey(&key);
    char * encryptedKey = (char *) malloc( sizeof(char) * length);
    for(int i = 0, j = 0; i < length; i++,j++){
        if(j >= key.length -1 )
            j = 0;

        encryptedKey[i] = ((str[i] + key.key[j])) % MODULO;
    }
    encryptedKey[length-1] = '\0';
    free(key.key);      
    return encryptedKey;
}

char * Decrypt(char * str){
    
    int length = getLength(str);
    Key key;
    getPolyAlphabeticKey(&key);
    char * decryptedKey = (char *) malloc( sizeof(char) * length);
    for(int i = 0, j = 0; i < length; i++,j++){
        if(j >= key.length -1)
            j = 0;
        decryptedKey[i] = (str[i] - key.key[j] + MODULO) % MODULO;   
    }
    free(key.key);  
    decryptedKey[length-1] = '\0';    
    return decryptedKey;
}


char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    return buf;
 }