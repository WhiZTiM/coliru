// Frota de taxi (Tarefa da OBI2005, Modalidade Programação Nível 1, Fase 1)
/*
Você deve escrever um programa que, dados
o preço do litro de álcool,o preço do litro de gasolina e os quilômetros por litro
que um carro bi-combustível realiza com cada um desses combustíveis,
determine se é mais econômico abastecer os carros com álcool ou com gasolina.
No caso de não haver diferença de custo entre abastecer com álcool ou gasolina dê preferência utilizar gasolina.
*/
#include <iostream>
using namespace std;

int main(){
//Entrada
double precoLitroAlcool;//preço por litro do álcool
double precoLitroGasolina;//preço por litro da gasolina
double rendimentoAlcool;//o rendimento (km/l) do carro utilizando álcool
double rendimentoGasolina;//o rendimento (km/l) do carro utilizando gasolina
//Capturando a entrada , 4 números reais em uma unica linha;
cin >> precoLitroAlcool >> precoLitroGasolina >> rendimentoAlcool >> rendimentoGasolina;

/*
Saída
A saída deve ser composta por uma única linha contendo
o caractere ‘A’ se é mais econômico abastecer a frota com álcool ou
o caractere ‘G’ se é mais econômico ou indiferente abastecer a frota com gasolina.
*/

/*
Para saber o mais economico  as pessoas costuma fazer o mesmo trajeto, geralmente ida e volta,
então comprarar os resultados.
Geralmente as pessoas fazem isso em uma viajem, a ida usam um combustivel e na volta o outro.

Para resolver este problema vamos escolher um trajeto de 1 km, por 2 motivos:
1º) O número 1 é o numero mais facil de multiplicar e dividir :)
2º) O rendimento foi medido em km e l, mas especificamente km/l


Este problema vai ser divido em três partes onde eu tenho que responder algumas perguntas:
1º Parte : Quantos litros de combustivel(Alcool ou Gasolina) o carro consume ao escolher um dos combustiveis percorrendo 1km?
2º Parte : Quanto é que custa o combustivel consumido usando o alcool e a gasolina?
3º Parte : É só comparar os custos do carro no trajeto de ida com o trajeto de volta para saber quem é o mais economico.
*/

//1º Parte : Quantos litros de combustivel(Alcool ou Gasolina) cada carro consume em 1km?
double combustivelAcoolConsumido;
double combustivelGasolinaConsumido;
//Lembre-se que a trajetória só tem 1 km na ida e na volta
//Caso não tenha entendido as formulas abaixo sugiro fazer uma regra de três com a formula do rendimento(km/l)
//rendimentoCombustivel = distancia percorrida(em km) / combustivelConsumido (litros)
//Observação: O numero 1 apareceu por escolhi as trajetorias de ida e volta igual a 1km.
combustivelAcoolConsumido=1/rendimentoAlcool;
combustivelGasolinaConsumido=1/rendimentoGasolina;

//2º Parte : Quanto é que custa o combustivel consumido usando o alcool e a gasolina?
double gastoUsandoAlcool;
double gastoUsandoGasolina;
//Caso não esteja entendo as formulas abaixo sugiro investigar a formula preçoLitroCombustivel(precoLitroAlcool ou precoLitroGasolina)
gastoUsandoAlcool=precoLitroAlcool*combustivelAcoolConsumido;
gastoUsandoGasolina=precoLitroGasolina*combustivelGasolinaConsumido;

//3º Parte : É só comparar os custos do carro no trajeto de ida com o trajeto de volta para saber quem é o mais economico.
if(gastoUsandoAlcool>=gastoUsandoGasolina){
    cout << "G";
}else{//Lembre-se que só executará este else se o if acima der falso
    cout << "A";
}
//Conclusão: criando variaveis com nomes que fazem sentido deixa a comparação do if muito mais facil de entender
return 0;
}
