#include<stdio.h>
#include<math.h>

//Sohel Shamshuddin Bargir - 142203002

float fact(int n){
	if(n <= 1){
		return 1;
	}
	return n * fact(n-1);
}

int main(){
	
	float  PI = 3.14159;
	int n ;
	int num ;
	printf("Enter x and number :");
	scanf("%d %d",&num,&number);
	
	float x = (num*3.14f)/180.0f;
	
	float ans = x;
	int powf = 3;
	
	for(int i = 0 ; i < n; i++){
		float temp = (pow(x,powf)/fact(powf));
		if(i % 2 != 0){
		ans +=  temp;
		}
		else
		ans -= temp;
		

		powfact += 2;
		
	}
	printf("\n%f",ans);
	return 0;
}
