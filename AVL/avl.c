#include<stdio.h>
#include<stdlib.h>
#include"avl.h"

void initAVL(AVL *t)
{
    *t = NULL;
    return;
}

int height(AVL t)
{
    if(!t)
          return -1;
    int rh = height(t->right);
   
    int lh = height(t->left);
    return lh > rh ? lh+1 : rh+1;
}
   

void updateBalanceFactor(AVL *t)
{
	node* p = *t;
   while(p)
   {
        p->balanceFactor = height(p -> left) - height(p -> right);
        p = p -> parent;    
   }


node* adjustImbalance(AVL *t)
{
    if(!(*t))
        return NULL;

    node *p = *t;
    node *imb = NULL;
    int flag = 0;

    while(p)
    {
        p -> balanceFactor = height(p -> left) - height(p -> right);

        if((abs(p -> balanceFactor) > 1) && !flag)
        {
            imb = p;
            flag = 1;
        }
        p = p -> parent;
    }
    
    return imb;

}


void insertNodeIntoAVL(AVL* t, int data)
{
    node *nn = (node*) malloc(sizeof(node));
    nn->data = data;
    nn->left = NULL;
    nn->right = NULL;
    nn->parent = NULL;
    nn->balanceFactor = 0;

    if (!(*t))
    {
        *t = nn;
        return;
    }

    node* p, *q;
    q = NULL;
    p = *t;

    while(p)
    {
        q = p; 

        if (nn->data < p->data)
            p = p->left;
        else if (nn->data > p->data)
            p = p->right;
        else
        {
            free(nn);
            return;
        }
    }

    if (nn->data < q->data)
        q->left = nn;
    else
        q->right = nn; 

    nn->parent = q;

    updateBalanceFactor(&q);
    node * imb = NULL;
    imb = adjustImbalance(&q);
    
    if(imb)
    {
        if(nn->data < imb->data)
        {
            if(imb->left)
            {
                if(nn-> data < imb->left->data)
                    LLRotation(t, imb);
                else
                    LRRotation(t, imb);
            }
            if(imb->right)
            {
                if(nn->data > imb->right->data)
                    RLRotation(t, imb);
            }
        }
        else
        {
            if(imb->left)
            {
                if(nn-> data < imb->left->data)
                    LRRotation(t, imb);
            }

            if(imb->right)
            {
                if(nn->data > imb->right->data)
                {
                    RRRotation(t, imb);
                }
                else
                {
                    RLRotation(t, imb);
                }
            }
        }

        // imb = adjustImbalance(&q->parent);
    }

    return;
}
void removeNodeIterative(AVL *t, int key)
{

    if(!(*t))
        return;

    node *p, *q;
    p = *t;

    while(p)
    {
        if(p -> data == key)
            break;

        q = p;

        if(p -> data > key)
            p = p -> left;
        else
            p = p -> right;
    }

    if(!p)
        return;

    
    // Node has no any children means it is a leaf node
    if(!p -> left && !p -> right)
    {
        if(p == *t)
        {
            *t = NULL;
            printf("Only root is remaning\n");
            free(p);
            return;
        }

        if(q -> right == p)
            q -> right = NULL;
        else if(q -> left == p)
            q -> left = NULL;

        balanceTree(t,q);
        // if(*t && (*t)->parent == q)
        //     *t = q;
        free(p);
        return;
    }

    if(p -> left && !p -> right)
    {
        if(p == *t)
        {
            *t = p -> left;
            // balanceTree(t,q);
            free(p);
            return;
        }

        if(q -> right == p)
            q -> right = p -> left;
        else if(q -> left == p)
            q -> left = p -> left;
        
        balanceTree(t,q);
        free(p);
        return;
    }

    if(p -> right && !p -> left)
    {
        if(p == *t)
        {
            *t = p -> right;
            // balanceTree(t,q);
            free(p);
            return;
        }

        if(q -> left == p)
            q -> left = p -> right;
        else if(q -> right == p)
            q -> right = p -> right;

        balanceTree(t,q);
        free(p);
        return;
    }

    // node has both childs
    node *m, *prev;

    m = p -> left;
    prev = NULL;

    while(m -> right)
    {
        prev = m;
        m = m -> right;
    }
    p -> data = m -> data;

    // removeNodeIterative(&(p -> left), p -> data);

    // balanceTree(&(p->left), p);

    return;
}

void balanceTree(AVL *t, node* nn)
{
    updateBalanceFactor(&nn->parent);
    node * imb = NULL;
    imb = adjustImbalance(&nn);
        
    while(imb)
    {
        if(nn->data < imb->data)
        {
            if(imb->left)
            {
                if(nn-> data < imb->left->data)
                    LLRotation(t, imb);
                else
                    LRRotation(t, imb);
            }
        }
        else
        {
            if(imb->right)
            {
                if(nn->data > imb->right->data)
                {
                    RRRotation(t, imb);
                }
                else
                {
                    RLRotation(t, imb);
                }
            }
        }

        imb = adjustImbalance(&nn->parent);
    }
    
}

void destroyTree(AVL *t)
{
    if(!(*t))
        return;

    destroyTree(&((*t)->left));
    destroyTree(&((*t)->right));
    free(*t);
    *t = NULL;

    return;
}

void LLRotation(AVL *t, node *A)
{  
    node* B = A -> left;
    node* BR = B -> right;
    node* AP = A -> parent;

    B -> parent = AP;
    
    if(!AP)
        *t = B;
    else
    {
        if(AP -> right == A)
        {
            AP -> right = B;
        }
        else
        {
            AP -> left = B;
        }
    }
    A -> parent = B;
    B -> right = A;
    A -> left = BR;

    if(BR)
        BR -> parent = A;
    
    B -> balanceFactor = 0;
    A -> balanceFactor = 0;
    return;
}

void RRRotation(AVL *t, node *A)
{
    node* B = A -> right;
    node* BL = B -> left;
    node* AP = A -> parent;

    B -> parent = AP;

    if(!AP)
        *t = B;
    else
    {
        if(AP -> right == A)
            AP -> right = B;
        else
            AP -> left = B;
    }

    B -> left = A;
    A -> parent =  B;
    A -> right = BL;

    if(BL)
        BL -> parent = A;

    A -> balanceFactor = 0;
    B -> balanceFactor = 0;

    return;
}

// LR -> RR + LL
void LRRotation(AVL *t, node *n)
{
    RRRotation(t, n->left);
    LLRotation(t, n);
    return;
}

// RL -> LL + RR
void RLRotation(AVL *t, node *n)
{
    LLRotation(t, n->right);
    RRRotation(t, n);
    return;
}

void inorder(AVL p)
{
    if(!p)
        return;

    inorder(p -> left);
    printf("%d %d \n", p->data, p->balanceFactor);
    inorder(p->right);
}
