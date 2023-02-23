#include<stdio.h>


int main()
{
  char c;
  printf("Enter character : ");
  scanf("%c",&c);
  char d;
  if(c >= 'A' && c<= 'Z'){
     c= c+32;
     printf("%c",c);
  }
  else
  {
     c = c-32;
     printf("%c",c);	
  }
  
  return 0;
}
