#include <iostream>
using namespace std;

void Tabellina(int V[]);
void spostaSinistra(int V[]);
void spostaDestra(int V[]);
void sostVocali(char frase[]);
int contCaratt(char frase[],char frase2[]);
void convMaiusc(char frase[]);
void copiaString(char frase[]);
void invString(char frase[], char frase2[]);
int lettComprese(char frase[]);
int contaVocali(char frase[]);
int contDoppie(char frase[]);
int lungString(char frase[]);


int main(){
    int V[6]={4,5,6,7,8,9};
    int y;
    int t[10],n,scelta;
    char frase[100]="Stringa Uno";
    char frase2[100]="Stringa Due";
    do{
    printf(" 1)Tabellina\n 2)Sposta a sinistra\n 3)sposta a destra\n 4)sostituisci vocali\n 5)contcaratt\n 6)convMaiusc\n 7)copia stringa\n 8)invstringa\n 9)lettcompres\n 10)conta vocali\n 11)contdoppie\n 12)lungstringa\n");
    
       printf("Fai la tua scelta, 0 per finire:");
       scanf("%d",&scelta);
       switch(scelta){
                      
                       
                      case 1:   Tabellina(V);
                      			system("PAUSE");
                                break;
                      case 2:   spostaSinistra(V);
                      			system("PAUSE");
                                break;
                      case 3:   spostaDestra(V);
                      			system("PAUSE");
                                break;
                      case 4:   sostVocali(frase);
                      			system("PAUSE");
                                break;
                      case 5:   y=contCaratt(frase,frase2);
                      			printf("%d",y);
                      			system("PAUSE");
                                break;
                      case 6:   convMaiusc(frase);
                      			system("PAUSE");
                                break;
                      case 7:   copiaString(frase);
								system("PAUSE");
                                break;
                      case 8:   invString(frase, frase2);
                      			system("PAUSE");
                                break;
                      case 9:   y=lettComprese(frase);
								printf("Ci sono %d lettere comprese tra A e G\n",y);
								system("PAUSE");

                                break;
                      case 10:  y=contaVocali(frase);
                      			printf("Ci sono %d vocali",y);
								system("PAUSE");
                                break;
                      case 11:  y=contDoppie(frase);
                      			printf("Ci sono %d doppie",y);
                      			system("PAUSE");
                                break;
                      case 12:  y=lungString(frase);
                      			printf("La stringa e' lunga %d caratteri",y);
                      			system("PAUSE");
                                break;
                      default:  printf("Scelta non valida.");
       }
    }while(scelta!=0);
                        
  system("PAUSE");	
  return 0;
}





void Tabellina(int V[]){
	int i, n, x=n;
	printf("Inserisci il numero per la tabellina: ");
	scanf("%d", &n);
	for(i=0;i<10;i++){	
		x=x+n;
		V[i]=x;
		printf("%d\n", V[i]);
	}
}

void spostaSinistra(int V[]){
    int i, x;
    x=V[0];
    for(i=0;i<6;i++){
     V[i]=V[i+1];
    }
    V[5]=x;
    for(i=0;i<6;i++){
     printf("%d",V[i]);
	}

}

void spostaDestra(int V[]){
 int i, x;
    x=V[5];
    for(i=4;i>-1;i--){
     V[i+1]=V[i];
    }
    V[0]=x;
    for(i=0;i<6;i++){
     printf("%d",V[i]);
	}
}


    
void sostVocali(char frase[]){
     int i;
     for(i=0;frase[i]!='\0';i++){
        if(frase[i]=='a'||frase[i]=='e'||frase[i]=='i'||frase[i]=='o'||frase[i]=='u'){
           frase[i]='E';
        }
     }
     printf("%s",frase);
}

int contCaratt(char frase[],char frase2[]){
     int i, cont=0;
     for(i=0;frase[i]!='\0';i++){
        if( frase[i]=frase2[i]){
            cont++;
        }
     }
    return cont; 
}

void convMaiusc(char frase[]){
     int i;
     for(i=0;frase[i]!='\0';i++){
        if(frase[i]>='a'&& frase[i]<='z'){
           frase[i]=frase[i]+'A'-'a';
        }
     }
     printf("%s",frase);
}

void copiaString(char frase[]){
     char frase3[10];
     int i,k=0;
     for(i=0;frase[i]!='\0';i++){
        if(frase[i]!=' '){
           frase3[k]=frase[i];
           k++;
        }
     }
     printf("\n%s",frase);
     printf("\n%s",frase3);
}

void invString(char frase[],char frase2[]){
     int i,k=5;
     for(i=0;frase[i]!='\0';i++){
        frase[k]=frase2[i];
        frase[i]=frase2[k];
        k--;
     }
     printf("%s",frase);
}

int lettComprese(char frase[]){
     int i, cont;
     for(i=0;frase[i]!='\0';i++){
        if(frase[i]=='A'||frase[i]=='a'){
           for(cont=0;frase[i]=='G'||frase[i]=='g';cont++){
           	return cont;
           }
        }
     } 
}

int contaVocali(char frase[]){
     int i,cont=0;
     for(i=0;frase[i]!='\0';i++){
        if(frase[i]=='a'||frase[i]=='e'||frase[i]=='i'||frase[i]=='o'||frase[i]=='u'){
           cont++;
        }
     }
    return cont; 
}

int contDoppie(char frase[]){
     int i,cont=0;
     for(i=0;frase[i]!='\0';i++){
        if(frase[i]==frase[i+1]){
           cont++;
        }
     }
    return cont; 
}
