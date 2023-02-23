#include <stdio.h>
int main() {
   int rows, d = 1, s, i, j;
   printf("Enter the number of rows: ");
   scanf("%d", &rows);
   for (i = 0; i < rows; i++) {
      for (s = 1; s <= rows - i; s++)
         printf("  ");
      for (j = 0; j <= i; j++) {
         if (j == 0 || i == 0)
            d = 1;
         else
            d = d * (i - j + 1) / j;
         printf("%4d", d);
      }
      printf("\n");
   }
   return 0;
}

