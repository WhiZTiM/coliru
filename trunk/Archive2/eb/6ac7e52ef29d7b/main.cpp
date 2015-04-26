// Gangorra(Tarefa da OBI2014, Modalidade Programação Junior, Fase 1)
#include <iostream>
using namespace std;
/*
Fazer um programa para saber se a gangorra esta equilibrada ou desequilibrada.
Caso esteja desequilibrada mostrar para que lado pendeu.
*/
int main(){
//Entrada
int pesoLadoEsquerdo;//Peso da criança do lado esquerdo
int pesoLadoDireito;//Peso da criança do lado direito
int comprimentoEsquerdo;//comprimento da gangorra do lado esquerdo
int comprimentoDireito;//comprimento da gangorra do lado direito
//Capturando a entrada , 4 números inteiros em uma unica linha
cin >> pesoLadoEsquerdo >> comprimentoEsquerdo >> pesoLadoDireito >> comprimentoDireito;

/*
 A gangorra do parquinho não é simétrica, UMA DAS EXTREMIDADES é MAIS LONGA QUE A OUTRA.
 Após brincar algumas vezes com um amigo de MESMO PESO,  ele percebeu que
 QUANDO ESTá EM UMA EXTREMIDADE, A GANGORRA SE DESEQUILIBRA PARA O LADO DELE
 (ou seja, ele fica na parte de baixo, e o amigo na parte de cima), mas
 quando eles trocam de lado, a gangorra se desequilibra para o lado do amigo.
 Sem entender a situação, Joãozinho pediu ajuda a outro amigo de outra série,
 que explicou que o comprimento do lado interfere no equilíbrio da gangorra, pois a gangorra estará equilibrada quando
    pesoLadoEsquerdo * comprimentoEsquerdo == pesoLadoDireito * comprimentoDireito
            multiplicacaoEsquerda          ==        multiplicacaoDireita   
Se equilibra quand 
O que jãozinho observou foi:
1º) Se equilibra quando a multiplicacaoEsquerda é igual a multiplicacaoDireita
2º)Seu amigo tem o mesmo peso que ele , então pesoLadoEsquerdo = pesoLadoDireito , que simplismente vou chamar de PESO
( Nesta situação vou chamar somente de PESO , pois não me importa se esta do lado esquerdo ou direito, é tudo igual mesmo)
3º)Uma extremidade é mais longa que o outra, eu só não sei qual é a mais longa , se a esquerda ou a direita.

Junta a observação 1º e 2 º) na formula, que dará uma pista
 PESO * comprimentoEsquerdo == PESO * comprimentoDireito

 Olha esta parte do texto "QUANDO ESTá EM UMA EXTREMIDADE, A GANGORRA SE DESEQUILIBRA PARA O LADO DELE "
 Quando esta na extremidade o comprimento é maior, então vai desequilibrar para o lado do comprimento maior(quando os pesos são iguais)
 Nesta situação: PESO * comprimentoMaior_ExtremidadeMaior > PESO * comprimento_ExtremidadeMenor
 Então eu concluo que desequilibra porque a multiplicação de cada lado fica diferente, mas não tem como saber para que lado se desequilibra,
 se por lado da multiplicação maior ou menor
 */
int  multiplicacaoEsquerda = pesoLadoEsquerdo * comprimentoEsquerdo;
int  multiplicacaoDireita  = pesoLadoDireito * comprimentoDireito;
if(multiplicacaoEsquerda==multiplicacaoDireita){
    cout << "0";//Equlibrado, o texto diz que se a multiplicação forem iguais a balança ficará equilibrada
}else if(multiplicacaoEsquerda>multiplicacaoDireita){
    cout << "Não tenho como saber pelo texto se devo por 1 ou -1, mas eu ainda tenho uma pista(os exemplos de saida) - Resolva";
}else{//Só lembrando, só entra neste else se AS DUAS OPERAÇÔES LOGICAS ACIMA DEREM FALSO
    cout << "Não tenho como saber pelo texto se devo por 1 ou -1, mas eu ainda tenho uma pista(os exemplos de saida) - Resolva";
}
//Conclusão, em qualquer parte do texto ou ate nos exemplos de entrada/saida pode esta escondida uma pista.
return 0;
}
