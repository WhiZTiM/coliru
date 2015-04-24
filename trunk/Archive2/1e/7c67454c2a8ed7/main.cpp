#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

int strlen(char *str)
{
    int total=0;

    while( str[total] != '\0')
        total++;

    return total;
}

int main() {
    int quadrado;
    char buffer[25];
    int qtd_matrizes;//Quantidade de matrizes para serem resolvidas
    cin >> qtd_matrizes;
    int matriz[100][20][20];
    int ordem[100];//Ordem das matrizes
    for(int i=0;i<qtd_matrizes;i++){
        cin >> ordem[i];
            for(int j=0;j<ordem[i];j++){
                for(int k=0;k<ordem[i];k++){
                    cin >> matriz[i][j][k];
                }
            }
    }
/*
[1]Maior elemento da coluna
*/
int maiorNumeroColuna[100][20];
int maiorNumero;
for(int i=0;i<qtd_matrizes;i++){

           for(int j=0;j<ordem[i];j++){
                maiorNumero=-1;
                for(int k=0;k<ordem[i];k++){
                    if(matriz[i][k][j]>maiorNumero){
                        maiorNumero=matriz[i][k][j];
                    } //if
                }//for k
                maiorNumeroColuna[i][j]=maiorNumero;
            }
    }




/*
[1]Fim Maior elemento da coluna
*/

/*
for(int i=0;i<qtd_matrizes;i++){
    for(int k=0;k<ordem[i];k++){
sprintf(buffer,"%d",maiorNumeroColuna[i][k]);
cout << strlen(buffer) << endl;
cout << maiorNumeroColuna[i][k] << endl;
}
}

*/



    for(int i=0;i<qtd_matrizes;i++){
        cout << "Quadrado da matriz #" << i+4 <<":" << endl;
            for(int j=0;j<ordem[i];j++){

                for(int k=0;k<ordem[i];k++){
                    sprintf(buffer,"%d",(maiorNumeroColuna[i][k]*maiorNumeroColuna[i][k]));
                    cout << setw(strlen(buffer));
                    cout << matriz[i][j][k]*matriz[i][j][k] << " ";
                }
                cout << endl;
            }
        cout << endl;
    }

    return 0;
}