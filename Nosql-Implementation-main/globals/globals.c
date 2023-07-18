#include "globals.h"
#include <stdlib.h>
#include<stdio.h>
void initGlobals(){
    globals.collection = (char*) malloc(sizeof(char) * SIZE);
    if(!globals.collection)
        exit(EXIT_FAILURE);

    globals.user = (char*) malloc(sizeof(char) * SIZE);
    if(!globals.user)
        exit(EXIT_FAILURE);

    globals.document = (char*) malloc(sizeof(char) * SIZE);
    if(!globals.document)
        exit(EXIT_FAILURE);

    globals.user[0] = '\0';
    globals.document[0] = '\0';
    globals.collection[0] = '\0';

return;
}

void destroyGlobals(){
    if(globals.collection)
        free(globals.collection);
    if(globals.user)
        free(globals.user);
    if(globals.document)
        free(globals.document);
return;
}


int getLength(char * str){
    int l = 0;
    char * p = str;
    while(*p != '\0'){
        p++;
        l++;
    }
    return l+1;
}

char* dataEncrypt(char * data){
    int i = 0;
    int index = 0;
    char *p = data;
    char * encrypted =(char *) calloc(getLength(data),sizeof(char));
    while(*p != '\0'){
        i+=3;
        encrypted[index++] =(char) ((*p) - i);
        if(i > 15)
            i = 0;
        p++;
    }
    encrypted[index] = '\0';
return encrypted;
}

char* dataDecrypt(char * encrypted){
    int i = 0;
    int index = 0;
    char *p = encrypted;
    char * data = calloc(getLength(encrypted),sizeof(char));
    while(*p != '\0'){
        i+=3;
        data[index++] = (*p) + i;
        if(i>15)
            i=0;
        p++;
    }
    data[index] = '\0';
return data;
}