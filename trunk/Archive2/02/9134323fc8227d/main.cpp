//Triângulo(Tarefa da OBI2014, Modalidade Programação nível 1, Fase 1)
#include <iostream>
using namespace std;

int main(){
/*
não dá para formar triângulos com três varetas de comprimentos quaisquer.
Ana fez uma pesquisa na internet e aprendeu que com três varetas é possível formar um triângulo quando,
para todas as varetas, vale a seguinte relação:
O COMPRIMENTO DA VARETA é MENOR DO QUE A SOMA DOS COMPRIMENTOS DAS OUTRAS DUAS VARETAS.
POR EXEMPLO, SE OS COMPRIMENTOS FOREM 6, 9 E 5, VAI DAR PARA FORMAR O TRIâNGULO,
POIS A RELAçãO VALE PARA AS TRêS VARETAS: 6 < 9 + 5, 9 < 6 + 5 E 5 < 6 + 9.
Mas, se os comprimentos forem, por exemplo, 4, 10 e 3, não vai dar para formar um triângulo,
porque a relação não vale para uma das varetas (pois 10 não é menor do que 3 + 4).

Neste problema, você precisa ajudar Ana e suas amigas a descobrir se, dados os comprimentos de quatro varetas,
é ou não é possível selecionar três varetas, dentre as quatro, e formar um triângulo!
*/
//Entrada
int vareta1,vareta2,vareta3,vareta4;
cin >> vareta1 >> vareta2 >> vareta3 >> vareta4;
/*
Com as 4 varetas dadas, preciso escolher tres para formar um triangulo.
Triangulos que contenha a vareta 1
Triangulo 1: vareta1 , vareta2 e vareta3
Triangulo 2: vareta1 , vareta2 e vareta4
Triangulo 3: vareta1 , vareta3 e vareta4
Não consigo criar mais triangulos diferentes que contenha a vareta1
Triangulo 4: vareta2 , vareta3 e vareta4
Não consigo criar mais nenhum triangulo diferente.
Tenho que testar se é possivel criar qualquer um dos 4 triangulos usando as regras ensinadas no texto da questão
*/
bool formaTriangulo1;//True se pode formar um triangulo1, ou falso se não pode
bool formaTriangulo2;//True se pode formar um triangulo2, ou falso se não pode
bool formaTriangulo3;//True se pode formar um triangulo3, ou falso se não pode
bool formaTriangulo4;//True se pode formar um triangulo4, ou falso se não pode
//A regra para se formar um triangulo é que um dos lados deve ser menor que a soma dos outros dois lados
//Para coompreensão desta ideia analise a parte em MAISCULA do texto lá em cima.
//Utilizamos o && porque é obrigatório todas as comparações serem verdadeiras para formar o Triangulo1.
formaTriangulo1=(   (vareta1<vareta2+vareta3) && //vareta1 é menor que a soma de vareta2+vareta3
                    (vareta2<vareta1+vareta3) && //vareta2 é menor que a soma de vareta1+vareta3
                    (vareta3<vareta1+vareta2)    //vareta3 é menor que a soma de vareta1+vareta2
                );
//Fazendo o mesmo para os demais possiveis triangulo
formaTriangulo2=((vareta1<vareta2+vareta4) && (vareta2<vareta1+vareta4) && (vareta4<vareta1+vareta2) );
formaTriangulo3=((vareta1<vareta3+vareta4) && (vareta3<vareta1+vareta4) && (vareta4<vareta1+vareta3) );
formaTriangulo4=((vareta2<vareta3+vareta4) && (vareta3<vareta2+vareta4) && (vareta4<vareta2+vareta3) );
/*
Saida
Seu programa deve produzir apenas uma linha contendo o caractere ‘S’, caso seja possível formar o triângulo;
ou o caractere ‘N’, caso não seja possível formar o triângulo.
*/
if(formaTriangulo1 || formaTriangulo2 || formaTriangulo3 || formaTriangulo4){//Se formar qualquer um dos 4 triangulos esta valendo
    cout << "S";
}else{//Senão puder formar nenhum dos 4 triangulos possiveis
    cout << "N";
}
//Novamente eu criei variaveis para deixar a operação logica dentro do if mais legivel

return 0;
}
