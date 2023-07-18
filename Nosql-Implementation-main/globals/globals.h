#ifndef GLOBALS_H
#define GLOBALS_H

typedef struct Globals{
    char * user;
    char * collection;
    char * document;
//    int isLoggedIn;
}Globals;

extern Globals globals;
#define SIZE 32

void initGlobals();
void destroyGlobals();

char* dataEncrypt(char * data);
char* dataDecrypt(char * data);
int getLength(char * str);

#endif


