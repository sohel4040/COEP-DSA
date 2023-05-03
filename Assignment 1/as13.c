#include<stdio.h>

int main()
{        
    char c;
    printf("Enter a character you want to check\n");
    scanf("%c",&c);
    
    // using if else statement
    // if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
    // {
    //     printf("Entered character is vowel");
    // }
    // else 
    // {
    //     printf("Entered character is consonant");
    // }
   
    // using switch statement
    switch(c)
    {
        case 'a': 
                printf("Entered character is vowel");
                break;
        case 'e': 
                printf("Entered character is vowel");
                break;
        case 'i': 
                printf("Entered character is vowel");
                break;
        case 'o': 
                printf("Entered character is vowel");
                break;
        case 'u': 
                printf("Entered character is vowel");
                break;
        case 'A': 
                printf("Entered character is vowel");
                break;
        case 'E': 
                printf("Entered character is vowel");
                break;
        case 'I': 
                printf("Entered character is vowel");
                break;
        case 'O': 
                printf("Entered character is vowel");
                break;
        case 'U': 
                printf("Entered character is vowel");
                break;
        
        default:
                printf("Entered character is consonant");
                break;

    }
    return 0;
}    