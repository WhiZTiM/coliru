#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX 20
void generamatrice(int matrice[MAX][MAX],int n, int m);
void printmatrice(int matrice[MAX][MAX],int n_str, int m_str, int n_end, int m_end);
void stampasottomatrice(int matrice[MAX][MAX],int n,int m, int p, int q);

main(void){
	int n,m,p,q,matrice[MAX][MAX];
	printf("dammi N e M\n");
	scanf("%d",&n);
	scanf("%d",&m);
	printf("dammi p(<n) e q(<m)\n");
	scanf("%d",&p);
	scanf("%d",&q);
	generamatrice(matrice,n,m);
	printmatrice(matrice,0,0,n,m);
	printf("\n\n");
	stampasottomatrice(matrice,n,m,p,q);
	system("PAUSE");
	
}

void generamatrice(int matrice[MAX][MAX],int n, int m){
	int i,j;
	srand(time(NULL));
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			matrice[i][j]=rand()%10;
		}
	}
}


void printmatrice(int matrice[MAX][MAX],int n_str, int m_str, int n_end, int m_end){
	int i,j;
	for(i=n_str;i<n_end;i++){
		for(j=m_str;j<m_end;j++){
			printf("%d ",matrice[i][j]);
		}
		printf("\n");
	}
}

void stampasottomatrice(int matrice[MAX][MAX],int n,int m, int p, int q){
	int r,c,sr,sc,somma,temp;
	for(r=0;r<n;r++){
		for(c=0;c<m;c++){
			temp=0;
			for(sr=r;sr<p+r;sr++){ if(sr<n) break;
				for(sc=c;sc<q+c;sc++){  if(sc<m) break;
					printf("%d ",matrice[sr][sc]);
					temp=temp+matrice[sr][sc];
				}
				printf("\n");
			}
			printf("\n----------\n");
		if (somma<temp)
		   somma=temp;
		}
		
	}
	
	
}