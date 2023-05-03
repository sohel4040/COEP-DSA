#include<stdio.h>
#include "Hackathon.h"

void initList(Club *c)
{
    *c = NULL;
     return;
}

int main()
{
    Club c;
    initList(&c);
    AddMember(&c,121,"s1");
    AddMember(&c,122,"s2");
    AddMember(&c,123,"s3");
    AddMember(&c,124,"s4");
    AddMember(&c,125,"s5");
    
    display(c);

    printf("\nNumber of members are : %d\n",count(c));

    deleteMember(&c,122);

    display(c);

    return 0;
}