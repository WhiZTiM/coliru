//Aviões de papel(Tarefa da OBI2009, Modalidade Programação Júnior, Fase 1)
#include <iostream>
using namespace std;

int main(){
//Criando as variaveis da Entrada
int ncompetidores;//número de competidores
int qtdPapelExistente;//quantidade de folhas de papel especial compradas  pela Diretora
int qtdPapelporCompetidor;//quantidade de folhas de papel especial que cada competidor deve receber
//Obtendo as entradas com o cin
cin >> ncompetidores >> qtdPapelExistente >> qtdPapelporCompetidor;
//Saida
//Seu programa deve escrever uma única linha contendo
//O caractere 'S' se a quantidade de folhas compradas pela Diretora é suficiente(As existentes)
//O caractere 'N' caso contrário(senão).
//Note que os caracteres devem ser letras maiúsculas.

//A quantidade de papel necessaria é (ncompetidores x qtdPapelporCompetidor)
int qtdPapelNecessaria;//Criando uma variavel para guardar o valor da quantidade de papel necessária
qtdPapelNecessaria=ncompetidores * qtdPapelporCompetidor;

//Agora faço o teste com o if.
//Observe como ficou facil de ler o if abaixo com a criação da variavel qtdPapelNecessaria
if(qtdPapelExistente>=qtdPapelNecessaria){//A quantidade de papel existente é maior ou igual(>=) a quantidade de papel necessária
    cout << "S";
}else{//Caso contrario ou senão(else)
    cout << "N";
}
return 0;
}