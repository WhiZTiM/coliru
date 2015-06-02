#include <stdio.h>
int i=0; 
int d;

void arrayadd(int A[5],int B[5], int R[5]);

int main(void){
    
	int A[5];
	int B[5];
	int R[5];
	
	i=0;
	for (i=0;i<5;i++){
		
		printf("Enter the A[%d] value: ",i);
		scanf("%d",&d);
		B[i]=d;
	}
	i=0;
	for (i=0;i<5;i++){
		printf("Enter the B[%d] value: ",i);
		scanf("%d",&d);
		B[i]=d;
		
	}
	
	printf("%d , %d, %d, %d, %d \n", R[0], R[1], R[2], R[3], R[4]);
	
	return 0;
}

void arrayadd(int A[5],int B[5], int R[5]){
	i=0;
	for(i=0;i<5;i++){
		R[i]=A[i]+B[i];
	}
	
}