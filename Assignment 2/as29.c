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
	scanf("%d %d",&num,&n);
	
	float x = (num*3.14f)/180.0f;
	
	
	float ans = 1;
	int powf = 2;
	for(int i = 0 ; i < n; i++){
		float term = (pow(x,powf)/fact(powf));
		if(i % 2 != 0){
		ans +=  term;
		}
		else
		ans -= term;
		

		powf+= 2;
		
	}
	printf("\n%f",ans);
	return 0;
}
