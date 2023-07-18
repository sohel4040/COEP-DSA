#include<stdio.h>
typedef struct node
{
    char *key, *value, *datatype;
    struct node* next;
} node;

typedef node* Pair;

typedef struct document
{
    char* documentId;
    Pair pairs;
} document;

typedef struct collectionNode
{
    document *document;
    struct collectionNode* next;
} collectionNode;

typedef collectionNode* Collection;

// Initilizing the pairs linkedlist
void initPair(Pair *pairs);
// For appending pair into pairs linkedlist
void appendToPair(Pair *pairs, char* key, char* value, char* datatype);
// This function helps to create a single document
int createDocument(char* collection, document* doc);
// This function helps to update the document
int updateDocument(char* collection, document* doc);
// This function helps to delete a single document
int deleteDocument(char* collection, char* documentKey);
// This function returns a single document as a document structure
document* getDocument(char *collection ,char* documentkey);
// return pairs linked list by fetching all key-value pairs from document 
Pair getAllPairsOfDocument(FILE *file);
// It returns all documents from collection as linkedlist named as Collection
Collection getAllDocumentFromCollection(char* collectionName);
// For initilizing the collection linkedlist
void initCollection(Collection *collection);
// For appending document to collection linkedlist
void addDocumentToCollection(Collection *collection, document* doc);
// This function accepts documentId and pairs as parameters and returns a document structure
document* initilizeAndCreateDocument(char* documentkey, Pair pairs);
// This function create key value pair mapping and attaches to a pairs linkedlist
void createPair(Pair *pairs,char* key, char* value, char* datatype);
// This function helps to delete single specific field from document
int deleteFieldFromDocument(char* collection, char* documentKey, char *pairkey);
// This is used to delete a single a pair from pairs linkedlist
int deletePair(Pair *pairs, char *pairKey);
// freeing up memory of pairs in a document
int freePairs(Pair* pairs);
// freeing up memory of a single document
int freeDocument(document* doc);
// freeing up memory of a single collection
int freeCollection(Collection* collection);
int validateDataFormatProtocol(char* line);
void displayDocument(document doc);
void displayCollection(Collection collection);

char* trim_spaces(char *str);
char* convertSinglePairIntoJSONString(node* singlePair);
char* convertSingleDocumentIntoJSONString(document *doc);
char* jsonfiyCollection(char* collectionpath);

// Exporting functions
int exportDocument(char* username, char* collectionName, char* documentId);
int exportCollectionHelper(char* username, char *collectionName);
int exportCollection(char* username, char *collectionName);
int exportUser(char *username);
int convertExportedDirectoryIntoTarFile(char* username);

