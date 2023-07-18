#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** map;
    int size;
} MyHashMap;


MyHashMap* myHashMapCreate() {
    MyHashMap* ret = malloc(sizeof(MyHashMap));
    ret->size = 10000;
    ret->map = calloc((ret->size) , sizeof(int*));
    return ret;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    int d = key;
    int n = obj->size;
    printf("Hash value: %d\n",d%n);
    while(1){
        if(obj->map[d%n] == NULL){
            obj->map[d%n] = malloc(2 * sizeof(int));
            obj->map[d%n][0] = key;
            obj->map[d%n][1] = value;
            break;
        }
        else if(obj->map[d%n][0] == key){
            obj->map[d%n][1] = value;
            break;
        }
        else
            d++;
    }  
}

int myHashMapGet(MyHashMap* obj, int key) {
    int d = key;
    int n = obj->size;
    while(1){
        if(obj->map[d%n] == NULL){
            return -1;
        }
        else if(obj->map[d%n][0] == key){
            return obj->map[d%n][1];
        }
        else 
           d++; 
    } 
    return -1;
}

void myHashMapRemove(MyHashMap* obj, int key) {
    int d = key;
    int n = obj->size;
    while(1){
        if(obj->map[d%n] == NULL){
            break;
        }
        else if(obj->map[d%n][0] == key){
            obj->map[d%n][0] = -1;
            break;
        }
        else 
           d++; 
    }    
}

void myHashMapFree(MyHashMap* obj) {
    int n = obj->size;
    for(int i = 0; i < n; i++){
        if(obj->map[i] != NULL)
            free(obj->map[i]);
    }
    free(obj->map);
    free(obj);
}
int main()
{
    MyHashMap* mp = myHashMapCreate();
    myHashMapPut(mp, 2,34);
    myHashMapPut(mp, 2,50);
    printf("%d\n",myHashMapGet(mp, 2));
    // myHashMapRemove(mp, 2);
    printf("%d\n",myHashMapGet(mp, 18));
    myHashMapFree(mp);


}