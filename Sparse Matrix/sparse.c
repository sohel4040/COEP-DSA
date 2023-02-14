#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int i,j;
    int data;
    struct node* right;
    struct node* down;

}node;

typedef struct sparse 
{
    int nc,nr;
    struct node** row;
    struct node** col;
}sparse;

void display(sparse *s)
{
    node *p;

    for(int i=0;i<s->nr;i++)
    {
        p = s->row[i];  

        while(p)
        {
            printf("%d->",p->data);
            p= p->right;
        }

        printf("\n");
    }
}

void swap(node **a,node **b)
{
	node** temp = a;
	*a = *b;
	*b = *temp;
}

void swapInteger(int *a,int *b)
{
	int *temp = a;
	a = b;
	b = temp;
}
void AttachNodeToSparseMatrix(sparse *s,int i, int j, int value)
{
    node * nn =(node*) malloc(sizeof(node));   
    nn->i=i;
    nn->j=j;
    nn->data=value;
    nn->right=NULL;
    nn->down=NULL;

    node *p;
    if(s->row[i]==NULL)
     s->row[i]= nn;
    else if(s->row[i]->right == NULL)
    {
        s->row[i]->right = nn;      
    }
    else 
    {
        p=s->row[i];
        while(p->right)
        {
            p=p->right;
        }
        p->right=nn;
    }

    if(s->col[j]==NULL)
     s->col[j]= nn;
    else if(s->col[j]->down == NULL)
    {
        s->col[j]->down= nn;
    }
    else 
    {
        p=s->col[j];
        while(p->down)
        {
            p=p->down;
        }
        p->down=nn;
    }
    
}

void initSparseWithoutFile(sparse *s,int nr, int nc)
{
    s-> nr = nr;
    s-> nc = nc;
    s-> row= (node**) malloc(sizeof(node*)* s->nr);
    s-> col= (node**) malloc(sizeof(node*)* s->nc);
    for(int i=0;i<(s->nr);i++)
    {
        s->row[i] = NULL;
    }
    for(int i=0;i<(s->nc);i++)
    {
        s->col[i] = NULL;
    }
}

void addTwoSparseMatrices(sparse * s1, sparse *s2,sparse *s3)
{
    if(s1->nr != s2->nr || s1->nc != s2->nc )
        return;
    
    initSparseWithoutFile(s3,s1->nr,s1->nc);
    
    node *r1, *r2;
    for(int i=0;i<s3->nr;i++)
    {
      r1 = s1->row[i];
      r2 = s2->row[i];

      while(r1 && r2)
      {
         if((r1 -> j == r2 -> j))
         {
            int sum = r1 -> data + r2 -> data; 
            if(sum != 0)  
                AttachNodeToSparseMatrix(s3,i,r1->j,sum);
            r1 = r1->right;
            r2 = r2->right;
         }
         else if( r1 -> j < r2 -> j)
         {
            AttachNodeToSparseMatrix(s3,i,r1->j, r1->data);
            r1 = r1->right;
         }
         else
         {
            AttachNodeToSparseMatrix(s3,i,r2->j, r2->data);
            r2 = r2->right;
         }
        
      }   
     while(r1)
      {
        AttachNodeToSparseMatrix(s3,i,r1->j,r1->data);
        r1 = r1 -> right;
      }
     while(r2)
      {
        AttachNodeToSparseMatrix(s3,i,r2->j,r2->data);
        r2 = r2 -> right;
      }
     
    }
}

void substractTwoSparseMatrices(sparse * s1, sparse *s2,sparse *s3)
{
    if(s1->nr != s2->nr || s1->nc != s2->nc )
        return;

    initSparseWithoutFile(s3,s1->nr,s1->nc);
    node *r1, *r2;
    for(int i=0;i<s3->nr;i++)
    {
      r1 = s1->row[i];
      r2 = s2->row[i];

      while(r1 && r2)
      {
         if((r1 -> j == r2 -> j))
         {
            int sum = r1 -> data - r2 -> data; 
            if(sum != 0)  
                AttachNodeToSparseMatrix(s3,i,r1->j,sum);
            r1 = r1->right;
            r2 = r2->right;
         }
         else if( r1 -> j < r2 -> j)
         {
            AttachNodeToSparseMatrix(s3,i,r1->j, r1->data);
            r1 = r1->right;
         }
         else
         {
            AttachNodeToSparseMatrix(s3,i,r2->j, -r2->data);
            r2 = r2->right;
         }
        
      }   
     while(r1)
      {
        AttachNodeToSparseMatrix(s3,i,r1->j,r1->data);
        r1 = r1 -> right;
      }
     while(r2)
      {
        AttachNodeToSparseMatrix(s3,i,r2->j,-r2->data);
        r2 = r2 -> right;
      }
     
    }
}

void transposeOfMatrix(sparse *s)
{
	node *p,*temp;
	for(int i=0;i<s->nc;i++)
    	{
		p=s->row[i];
		
		while(p)
		{
		    temp = p->right;
		    
		    swap(&p->right,&p->down);
		    p= temp;
		    
		}
    }
	
	node **temp1 = s->row;
	s->row=s->col;
	s->col=temp1;
	
	swapInteger(&s->nc,&s->nr);
		
}

void initSparse(sparse *s, char filename[])
{
    FILE *ptr;
    ptr = fopen(filename,"r");
    fscanf(ptr,"%d %d",&s->nr,&s->nc);

    s->row= (node**) malloc(sizeof(node*)* s->nr);
    s->col= (node**) malloc(sizeof(node*)* s->nc);

    for(int i=0;i<(s->nr);i++)
    {
        s->row[i]=NULL;
    }
    for(int i=0;i<(s->nc);i++)
    {
        s->col[i]=NULL;
    }
    int d;
    for(int i=0;i<(s->nr);i++)
    {
        for(int j=0;j<(s->nc);j++)
        {
                fscanf(ptr,"%d",&d);
                if(d!=0)
                AttachNodeToSparseMatrix(s,i,j,d);  
        }
    }
}

int checkIfSymmetric(sparse *s)
{
	node *r, *c;
	for(int i=0;i<s->nr;i++)
	{
		r = s->row[i];
		c = s->col[i];
		while( r && c){
		
		if(r -> i != c -> i && r -> j != c -> j){
		if(r-> i == c -> j && r-> j == c -> i && r->data != c->data)
		{
			return 0;
		}
		}
		r = r->right;
		c = c->down;
		}
	}
	
	if(r || c)
		return 0;

	
	return 1;
}


int main()
{

    sparse s2,s3,s4,s5;
    initSparse(&s2,"input1.txt");
    initSparse(&s3,"input2.txt");
    s5 = s3;

    printf("Transpose of a matrix is:\n");
    transposeOfMatrix(&s5);
    display(&s5);

    if(checkIfSymmetric(&s2))
    {
    	printf("Symmetric\n");
    }
    else 
    {
    	printf("Not symmetric\n");
    }

    printf("First matrix is:\n");
    display(&s2);
    printf("Second matrix is:\n");
    display(&s3);

    printf("Addition of two matrices is:\n");
    addTwoSparseMatrices(&s2,&s3, &s4);
    display(&s4);

    printf("Substraction of two matrices is:\n");
    substractTwoSparseMatrices(&s2,&s3, &s5);
    display(&s5);
    return 0;
}
