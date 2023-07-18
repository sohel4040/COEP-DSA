#include <stdio.h>
#include <stdlib.h>
#include "DocumentHashMap.h"
#include <string.h>
#include <limits.h>
#include "../globals/globals.h"

#define STRING 1 
#define CHARACTER 2
int getDocumentInHashMap(DocumentHashMap *);
DocumentHashMap tnode = NULL;
char collectionPath[100]  = "";
char documentName[100] = "";

int getDocumentInHashMap(DocumentHashMap *);
int validateDocument(char* docname);
Pair findAndFetchDocument(char*);
Pair updateValue(char* ,char* ,char* );

int max(int a, int b)
{
   return a > b ? a : b;
}

int heightOfTree(DocumentHashMap tNode)
{
    if (!tNode)
        return -1;

    return 1 + max(heightOfTree(tNode->left), heightOfTree(tNode->right));
}

void initDocumentHashMap()
{
    tnode = NULL; // Initializing a structure
}

void reassignBalanceFactor(DocumentHashMap* Qnode)
{
    documentHashmap* temp = *Qnode;
    while (temp)
    {
        temp->bf = heightOfTree(temp->left) - heightOfTree(temp->right); // Assigning balance factor to documentHashmap as left height - right height
        temp = temp->parent;
    }
    return;
}

DocumentHashMap getimBalancedNode(DocumentHashMap tdocumentHashmap)
{
    // DocumentHashMap tdocumentHashmap = tnode;
    if (!tdocumentHashmap)
        return NULL;
    documentHashmap* temp = tdocumentHashmap; // Imbalanaced documentHashmap is that documentHashmap who has balance factor apart from 0,1,-1
    while (temp)
    {
        // printf("\nTemp : %s %d",temp -> key,temp -> bf);
        if (temp->bf >= 2 || temp->bf <= -2)
            return temp;  // Traversing whole the parent ancestor tree for finding imbalanced documentHashmap
        temp = temp->parent;
    }
    return NULL;
}


void LLRotation(DocumentHashMap *tdocumentHashmap)  //Rotate whole tree in right direction
{
    DocumentHashMap mainTdocumentHashmap = tnode;
    documentHashmap* A = (*tdocumentHashmap);
    documentHashmap* B = A->left;
    documentHashmap* BR = B->right;
    documentHashmap* AP = A->parent;
    B->parent = AP;
    if (!AP)
        tnode = B;
    else
    {
        if (AP->right == A)
            AP->right = B;
        else
            AP->left = B;
    }
    A->parent = B;
    B->right = A;
    A->left = BR;
    if (BR)
        BR->parent = A;
    A->bf = 0;
    B->bf = 0;

    reassignBalanceFactor(&A);          //We have rotated the tree using pointers , now reassingning its bf

    return;
}

void RRRotation(DocumentHashMap *tdocumentHashmap ) //Rotate tree to left
{
    DocumentHashMap mainTdocumentHashmap = tnode;
    documentHashmap* A = (*tdocumentHashmap);
    documentHashmap* B = A->right;
    documentHashmap* BR = B->left;
    documentHashmap* AP = A->parent;
    B->parent = AP;
    if (!AP)
        tnode = B;
    else
    {
        if (AP->right == A)
            AP->right = B;
        else
            AP->left = B;
    }
    A->parent = B;
    B->left = A;
    A->right = BR;
    if (BR)
        BR->parent = A;
    A->bf = 0;
    B->bf = 0;
    reassignBalanceFactor(&A);  //We have rotated the tree using pointers , now reassingning its bf
}
void LRRotation(DocumentHashMap *tdocumentHashmap)
{
    RRRotation(&(*tdocumentHashmap)->left);     //Rotate left subtree and then rotate that updated tree to right
    LLRotation(tdocumentHashmap);
}

void RLRotation(DocumentHashMap *tdocumentHashmap)
{
    LLRotation(&(*tdocumentHashmap)->right); //Rotate right subtree and then rotate that updated tree to left
    RRRotation(tdocumentHashmap);
}

void getBalancedTree(documentHashmap* nodeImbalance){
     documentHashmap* imBalancedNode = getimBalancedNode(nodeImbalance);
  
    if (!imBalancedNode)
        return;
    // printf("\nImbalaned documentHashmap : %s , bf : %d\n", imBalancedNode->key, imBalancedNode->bf);
    if (imBalancedNode->bf == -2)
    {
        if (imBalancedNode->right->bf == 0 || imBalancedNode->right->bf == -1) 
            RRRotation(&imBalancedNode);
        else
            RLRotation(&imBalancedNode);
    }
    else if (imBalancedNode->bf == 2)
    {
        if (imBalancedNode->left->bf == 0 ||imBalancedNode->left->bf == 1 )
            LLRotation(&imBalancedNode);
        else  
            LRRotation(&imBalancedNode);        
    }
    return ;
}

DocumentHashMap mallocateAdocumentHashmap(char* key,char* value,char* datatype)
{
    documentHashmap *newdocumentHashmap = (documentHashmap*)malloc(sizeof(documentHashmap)); // Mallocating a documentHashmap and initializing the structure
    if(!newdocumentHashmap){
        return NULL;
    }
    newdocumentHashmap -> key = (char*) malloc(sizeof(char) * strlen(key));
    if(!newdocumentHashmap -> key){
        free(newdocumentHashmap);
        return NULL;
    }
    newdocumentHashmap -> value = (char*) malloc(sizeof(char) * strlen(value));
    if(!newdocumentHashmap -> value){
        free(newdocumentHashmap -> key);
        free(newdocumentHashmap);
        return NULL;

    }
    newdocumentHashmap -> datatype = (char*) malloc(sizeof(char) * strlen(datatype));
    if(!newdocumentHashmap -> datatype){
        free(newdocumentHashmap -> key);
        free(newdocumentHashmap -> value);
        free(newdocumentHashmap);
        return NULL;
    }

    strcpy(newdocumentHashmap -> key ,key);
    strcpy(newdocumentHashmap -> value ,value);
    strcpy(newdocumentHashmap -> datatype ,datatype);

    newdocumentHashmap->left = newdocumentHashmap->right = newdocumentHashmap->parent = NULL;
    newdocumentHashmap->bf = 0;
    return newdocumentHashmap;
}

int insertIntoDocumentHashMap(char* key,char* value,char* datatype)
{
    documentHashmap* newdocumentHashmap = mallocateAdocumentHashmap( key,value,datatype);
    if(!newdocumentHashmap){
        return INT_MIN;
    }
    if (!tnode)
    {
        tnode = newdocumentHashmap;
        return 1;
    }

    documentHashmap* p = tnode;
    documentHashmap* q = NULL;

    while (p)
    {
        q = p;
        int result = strcmp(p -> key , key);     //Return 0 -> strings are equal , 1 -> First string is greater, 2 -> second string is greater
        if (result == 0)
        {
            strcpy(p -> value,value) ;
            strcpy(p -> datatype,datatype) ;        //If same value present just UPDATE
            free(newdocumentHashmap);
            return -1;
        }
        else if (result > 0)        //If string 1 is greater , go left
            p = p->left;
        else
            p = p->right;
    }
    int res = strcmp(q-> key, key);
    if (res > 0)
        q->left = newdocumentHashmap;
    else
        q->right = newdocumentHashmap;

    newdocumentHashmap->parent = q;
    reassignBalanceFactor(&q);      //Reassinging balanace factor and  getting imbalanced documentHashmap
    getBalancedTree(q);
    return 1;
}

void createPairToInsertIntoDocument(Pair* pair, documentHashmap* temp){
    if(!temp){
        return ;
    }    
    createPairToInsertIntoDocument(pair,temp -> left);
    appendToPair(pair,temp -> key,temp -> value,temp -> datatype);
    createPairToInsertIntoDocument(pair,temp -> right);
}
int helpInsertingIntoDocumentFile(Pair* pair){
    sprintf(collectionPath, ".root/%s/%s", globals.user, globals.collection);
    strcpy(documentName,globals.document);
    node* temp = *pair;
    
    while(temp){
        int status = insertIntoDocumentHashMap(temp->key,temp->value,temp -> datatype);
        if(status == INT_MIN){
            destroyTree(&tnode);
            return INT_MIN;
        }
        temp = temp -> next;
    }
    if(!tnode){
        return INT_MIN;
    }
    Pair newPair ; 
    initPair(&newPair);
    createPairToInsertIntoDocument(&newPair,tnode);
    document* docs = initilizeAndCreateDocument(globals.document, newPair);
    int status = createDocument(collectionPath, docs);
    if( status == 0){
        destroyTree(&tnode);
        return 0;
    }

    return 1;
}
 void getBrackets(int brackets){
        if(brackets == STRING){
            printf("\"");
        } 
        else if(brackets == CHARACTER){
            printf("\'");
        }
    }
void displayValueWithBrackets(DocumentHashMap tdocumentHashmap){
    int brackets = 0;
    if(strcmp(tdocumentHashmap -> datatype , "STRING") == 0){
        brackets = STRING;
    }
    else if(strcmp(tdocumentHashmap -> datatype , "CHARACTER ") == 0)
    {
        brackets = CHARACTER;
    }
    getBrackets(brackets);
    if(tdocumentHashmap -> datatype == "BOOLEAN"){
        if(strcmp(tdocumentHashmap -> value,"T") == 0){
            printf("TRUE");
        }
        else if(strcmp(tdocumentHashmap -> value,"F") == 0){
            printf("FALSE");
        }
    }
    else
        printf("%s",tdocumentHashmap -> value );
    getBrackets(brackets);
}
void showDocs(DocumentHashMap tdocumentHashmap)
{
    if (!tdocumentHashmap)
        return;

    showDocs(tdocumentHashmap->left);
    printf("%s : %s",tdocumentHashmap -> key ,tdocumentHashmap -> value);
    printf("\n");
    showDocs(tdocumentHashmap->right);
}
void showFieldsDocuments()
{
    if(!validateDocument(globals.document))
        destroyTreeHelper();
    if(!tnode){
        int result = getDocumentInHashMap(&tnode);
        if(!result)
            return;
    }
    printf("\n");
    showDocs(tnode);
    printf("\n");
}


void preOrder(DocumentHashMap tdocumentHashmap)
{

    if (!tdocumentHashmap)
        return;

    printf(" { KEY : %s , BF : %d  , L : %s , R : %s  } \n",tdocumentHashmap->key ,tdocumentHashmap -> bf,tdocumentHashmap -> left ? tdocumentHashmap -> left -> key : NULL,
    tdocumentHashmap -> right ? tdocumentHashmap -> right -> key : NULL);
    preOrder(tdocumentHashmap->left);
    preOrder(tdocumentHashmap->right);
}

void removedocumentHashmapHelper(DocumentHashMap* parent)
{
    DocumentHashMap tdocumentHashmap = tnode;
    if(!(*parent))
        return;
    reassignBalanceFactor(parent);
    getBalancedTree(tdocumentHashmap);

    if((tdocumentHashmap) && (tdocumentHashmap) -> parent &&  (tdocumentHashmap) -> parent == (*parent))
        tdocumentHashmap = *parent;
}
int getDocumentInHashMap(DocumentHashMap *tnode){
    sprintf(collectionPath, ".root/%s/%s", globals.user, globals.collection);
    document* fetchData =  getDocument(collectionPath,globals.document);

    Pair newPair = fetchData -> pairs;
        while(newPair){
            // printf("\nDEBUG : %s",newPair -> value);
            int status = insertIntoDocumentHashMap(newPair->key,newPair->value,newPair-> datatype);
            if(status == INT_MIN){
                destroyTree(tnode);
                return 0;
            }
            newPair = newPair -> next;
        }
    return 1;
}
int validateDocument(char* docname){
    return (strcmp(docname,documentName)  == 0);
}
int helpRemoveFieldFromDocument(char* collectionName,char* documentName,char* key){
 char collectionPath[100]  = "";
    sprintf(collectionPath, ".root/%s/%s", globals.user, globals.collection);
    if(!validateDocument(globals.document))
        destroyTreeHelper();
    if(!tnode){
        int result = getDocumentInHashMap(&tnode);
        if(!result)
            return INT_MIN;
    }
    Pair getDocuemnt = findAndFetchDocument(key);
    if(!getDocuemnt){
        return 0;
    }
    int result = removedocumentHashmap(key);
    if(!result)
        return 0;

    Pair newPair;
    initPair(&newPair);
    DocumentHashMap temp = tnode;
    createPairToInsertIntoDocument(&newPair,tnode);
    
    int status = deleteFieldFromDocument(collectionPath, documentName, key); 
    if(!status){
        insertIntoDocumentHashMap(getDocuemnt->key,getDocuemnt->value,getDocuemnt->datatype);
        return INT_MIN;
    }
}
int removedocumentHashmap( char *key)
{
    DocumentHashMap tdocumentHashmap = tnode;
    documentHashmap *p, *q;
    if (!tdocumentHashmap)
        return 0;

    p = tdocumentHashmap;
    while (p)
    {
        int result = strcmp(p -> key, key);
        if (result == 0)
            break;
        q = p; // Search for presence of documentHashmap and make pointer q following p
        if (result > 0)
            p = p->left;
        else
            p = p->right;
    }
    if (p){
        // return 1
    }
        // printf("%s Found\n", p->data);
    
    if (!p){
        // printf("\n %s Not Found\n", key);
        return 0; // documentHashmap not present
    }
    // Now 4 cases
    
    // leaf documentHashmap
    int flag = 0;
    if (!p->right && !p->left)
    {
        documentHashmap *deletedocumentHashmap = p;
        documentHashmap *temp = deletedocumentHashmap->parent;
        if (p == tdocumentHashmap) // There is only 1 documentHashmap (root documentHashmap)
        {
            tdocumentHashmap = NULL;
            tnode = NULL;

        }
        else
        {
            if (q->left == p)
                q->left = NULL;
            else
                q->right = NULL;
            
            p -> parent = NULL;
        }
         free(deletedocumentHashmap);
        removedocumentHashmapHelper(&temp);

        return 1;
    }
        //1 child -> Only left child exists
    if (!p->right && p->left)
    {
        
        documentHashmap* deletedocumentHashmap = p;
        documentHashmap* temp = deletedocumentHashmap->parent;
        if (p == tdocumentHashmap) // There is root with only left child
        {
            p -> left -> parent = (tdocumentHashmap) -> parent;
            tdocumentHashmap = p->left;
            tnode = p->left;

        }
        else
        {
            if (q->left == p)
                q->left = p->left;
            else
                q->right = p->left;
            p -> left -> parent = q;
        }

         free(deletedocumentHashmap);
        removedocumentHashmapHelper(&temp);

        return 1;
    }
    //1 Child , Only right child exists
    else if (p->right && !p->left)

    {
        documentHashmap* deletedocumentHashmap = p;
        documentHashmap* temp = deletedocumentHashmap->parent;
        if (p == tdocumentHashmap)
        {
            p -> right -> parent = (tdocumentHashmap) -> parent;
            tdocumentHashmap = (deletedocumentHashmap->right);
            tnode = (deletedocumentHashmap->right);

        }
        else
        {
            if (q->left == p)
                q->left = p->right;
            else
                q->right = p->right;
            
            p -> right -> parent = q;
        }
        free(deletedocumentHashmap);
        removedocumentHashmapHelper(&temp);

        return 1;
    }
    //2 Childs i.e there exits both left and right
    else if (p->right && p->left)
    {
        documentHashmap *temp, *preecedingPointer; // There is root with left and right child
        preecedingPointer = p->left;
        temp = preecedingPointer->right;
        documentHashmap* parentOfTemp = NULL;
        if (!temp)
        {
            strcpy(p -> key, preecedingPointer ->key);
            p->left = preecedingPointer->left;
            if(preecedingPointer -> left)
            preecedingPointer -> left -> parent = p;
            parentOfTemp = preecedingPointer->parent;
             free(preecedingPointer);
        }
        else
        {
            while (temp->right)
            {
                preecedingPointer = temp;
                temp = temp->right;
            }
            
            p -> key = (char*)realloc(p -> key,sizeof(char)*strlen(temp -> key));
            p -> value = (char*)realloc(p -> value,sizeof(char)*strlen(temp -> value));
            p -> datatype = (char*)realloc(p -> datatype,sizeof(char)*strlen(temp ->datatype));

            strcpy(p-> key, temp-> key);
            strcpy(p-> value, temp-> value);
            strcpy(p-> datatype, temp-> datatype);


            parentOfTemp = preecedingPointer;
            if(temp -> left){
                preecedingPointer -> right = temp -> left;
                temp -> left -> parent = preecedingPointer; //EDGE CASE , MISSING CASE
            }
            else
            preecedingPointer->right = NULL;
             free(temp);
        }
        removedocumentHashmapHelper(&parentOfTemp);
        return 1;
    }
}

void destroyTree(DocumentHashMap *deleteNode)
{
    if (!(*deleteNode))
        return;

    destroyTree(&(*deleteNode) -> left);
    destroyTree(&(*deleteNode) -> right);

    free(*deleteNode);

    *deleteNode = NULL;
    return;
}
void destroyTreeHelper(){
    destroyTree(&tnode);
}


Pair findAndFetchDocument(char* key){
    Pair temp ;
    initPair(&temp);
    DocumentHashMap tdocumentHashmap = tnode;
    documentHashmap* p = tdocumentHashmap;
    while(p){
        int result = strcmp(key,p -> key);
        if(result == 0){
            appendToPair(&temp,p -> key, p -> value,
            p -> datatype);
            return temp; 
        }
        else if(result > 0){
            p = p -> right;
        }
        else{
            p = p -> left;
        } 
    }
    return temp;
}
void displayPair(Pair newPair){
    if(!newPair){
        printf("Field does not exist\n");
        return ;
    }

    printf("%s:", newPair -> key);
    printf("%s\n", newPair -> value);
}
int searchTheDocumentInFile(char* key){
        if(!validateDocument(globals.document))
            destroyTreeHelper();
        int result = getDocumentInHashMap(&tnode);
        if(!result){
            return INT_MIN;
        }
        Pair getDoc = findAndFetchDocument(key);
        // printf("\nField Found\n");
        displayPair(getDoc);
    return 1;
}
int helpUpdatingField(char* key,char* value,char* datatype){
    sprintf(collectionPath, ".root/%s/%s", globals.user, globals.collection);
    if(!validateDocument(globals.document))
        destroyTreeHelper();
     if(!tnode){
        int result = getDocumentInHashMap(&tnode);
        if(!result){
            return INT_MIN;
        }
     }

    Pair result = updateValue(key,value,datatype);
    if(!result){
        insertIntoDocumentHashMap(key,value,datatype);
    }
    document* docs = (document*)malloc(sizeof(document));
    docs->documentId = globals.document;
    initPair(&docs->pairs);
    DocumentHashMap temp = tnode;
    createPairToInsertIntoDocument(&docs->pairs,tnode);
    int status = updateDocument( collectionPath, docs);
   
    if(!status){
        return INT_MIN;
    }
    return 1;
}

int helpUpdatingTheDocument(Pair newPair){
    Pair mainPair = newPair;
    int result = 0;
    while(mainPair ){
        int status = helpUpdatingField(mainPair->key, mainPair-> value,mainPair -> datatype);
        if(status)
        {
            result = 1; 
        }
        mainPair = mainPair -> next;
    }
    return result ; //Result 1 Indicates some updates done , Result 0 indicatest no updates done
}

Pair updateValue(char* key,char* value,char* datatype){
    Pair newPair;
    initPair(&newPair);

    documentHashmap* p = tnode;
    while(p){
        int result = strcmp(key,p -> key);
        if(result == 0){
            appendToPair(&newPair,key,value,datatype);
            strcpy(p -> value, value);
            strcpy(p -> datatype, datatype);
            return newPair; 
        }
        else if(result > 0){
            p = p -> right;
        }
        else 
            p = p -> left;
    }
    return 0;
}