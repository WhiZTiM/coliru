/*
 * redeotica.c
 *
 *  Created on: 23/05/2015
 *      Author: Danillo Lima
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define COL_GRAFO 3


typedef struct Grafo *Apontador;
typedef int Pilha;

typedef struct Grafo {
    int numVertices;
	int numArestas;
	int **matrizAdjacencia;
	Apontador proximo;
}Grafo;

typedef struct ListaGrafo {
	Apontador primeiro, ultimo;
}ListaGrafo;

void InicializaGrafo(ListaGrafo *lista);
void LeEntrada(ListaGrafo *lista, int algoritmo);
int **CriaMatrizDeAdjacencia(int tamanho, int algoritmo);
void InsereGrafo(ListaGrafo *lista, int numArestas, int numVertices, int algoritmo);
void InsereAresta(int **matriz, int origem, int destino, int peso);
int MaiorPesoDeAresta(int **matriz, int numVertice);
void GeraSaidaPadrao(ListaGrafo *lista, int algoritmo);
void LiberaGrafo(ListaGrafo *lista);
int **LiberaMatrizDeAdjacencia(int **matriz, int tamanho);
void Kruskal(int **matriz, int numVertices, int numArestas, int teste);
int Raiz(int vertice, int pesoAresta[]);
void Reoderna(int i, int j,int pesoAresta[]);
void IniciaVetorComZero(int vetor[], int tamanho);
Pilha *PilhaNova(int tamanho);
int PilhaVazia(Pilha *p, int tamanho);
void PilhaEmpilha(Pilha *p, int *tamanhoPilha, int elemento, int distancia[], int quantidadeDeAcessos[]);
void PilhaDesempilha(Pilha *p, int *tamanhoPilha, int elemento);
int PesquisaElementoNaPilha(Pilha *p, int elemento);
void CalculaDistanciaPilha(Pilha *p, int *tamanhoPilha, int elemento, int distancia[], int quantidadeDeAcessos[]);
void PilhaDestroi(Pilha *p);

/*====================Pilha================================*/

void IniciaVetorComZero(int vetor[], int tamanho)
{
	int i;
	for(i=0; i<tamanho; i++) vetor[i] = 0;
}

Pilha *PilhaNova(int tamanho)
{
	Pilha *pilha = (Pilha *)malloc(tamanho * sizeof(Pilha));
	int i;
	for(i=0; i<tamanho; i++)
	{
		pilha[i] = -1;
	}
	return pilha;
}

int PilhaVazia(Pilha *p, int tamanho)
{
	int i = 0;
	while(i < tamanho)
	{
		if(p[i] != -1) return 0;
	}
	return 1;
}

void PilhaEmpilha(Pilha *p, int *tamanhoPilha, int elemento, int distancia[], int quantidadeDeAcessos[])
{
	if(PesquisaElementoNaPilha(p, elemento))
	{
		CalculaDistanciaPilha(p, tamanhoPilha, elemento, distancia, quantidadeDeAcessos);
		PilhaDesempilha(p, tamanhoPilha, elemento);
	}
	(*tamanhoPilha)++;
	p[elemento] = (*tamanhoPilha);
}

void PilhaDesempilha(Pilha *p, int *tamanhoPilha, int elemento)
{
	int aux = p[elemento];
	p[elemento] = -1;
	int i = 0;
	while(i < *tamanhoPilha)
	{
		if(aux < p[i]) p[i]--;
		i++;
	}
	(*tamanhoPilha)--;
}

int PesquisaElementoNaPilha(Pilha *p, int elemento)
{
	if(p[elemento] != -1) return 1;
	else return 0;
}

void CalculaDistanciaPilha(Pilha *p, int *tamanhoPilha, int elemento, int distancia[], int quantidadeDeAcessos[])
{
	distancia[elemento] = distancia[elemento] + ((*tamanhoPilha) - p[elemento]);
	quantidadeDeAcessos[elemento]++;
}

void PilhaDestroi(Pilha *p)
{
	free(p);
}

/*====================Kruskal================================*/
int Raiz(int vertice, int pesoAresta[])
{
	while(pesoAresta[vertice] != vertice)
    {
    	vertice = pesoAresta[vertice];
    }
    return vertice;
}

void Reoderna(int i, int j, int pesoAresta[])
{
	if(j > i) pesoAresta[j] = i;
    else pesoAresta[i] = j;
}

void Kruskal(int **matriz, int numVertices, int numArestas, int teste)
{
	//localidade e referencia
	Pilha *pilha = PilhaNova(numVertices);
	int distancia[numVertices];
	int quantidadeAcesso[numVertices];
	IniciaVetorComZero(distancia, numVertices);
	IniciaVetorComZero(quantidadeAcesso, numVertices);
	int tamanhoPilha = 0;


    int count, i, min, j, u, v, k;
    int arvoreMinima[numVertices][numVertices];
    int pesoAresta[numVertices];
    int matrizPesoAux[numVertices][numVertices];
    count = k = 0;
    for(i = 0; i < numVertices; i++)
    {
        pesoAresta[i] = i;
    }
    while(count < numVertices)
    {
        min = INT_MAX;
        for(i = 0; i < numVertices; i++)
        {
            for(j = i+1;j < numVertices; j++)
            {

                if(matriz[i][j] < min)
                {
                    min = matriz[i][j];
                    u = i;
                    v = j;
                    PilhaEmpilha(pilha, &tamanhoPilha, i, distancia, quantidadeAcesso);
                    PilhaEmpilha(pilha, &tamanhoPilha, j, distancia, quantidadeAcesso);
                }
            }
        }
        PilhaEmpilha(pilha, &tamanhoPilha, min, distancia, quantidadeAcesso);
        if(min != INT_MAX)
        {
            i = Raiz(u, pesoAresta);
            j = Raiz(v, pesoAresta);
            if (i != j)
            {
                arvoreMinima[k][0] = u;
                arvoreMinima[k][1] = v;

                k++;

                Reoderna(i,j,pesoAresta);
            }
        matrizPesoAux[u][v] = matrizPesoAux[v][u] = matriz[u][v];
        matriz[u][v] = matriz[v][u] = INT_MAX;

        }
        count +=1;
    }

    if(count != numVertices)
    {
        printf("spanning tree not exist\n");
    }

    if(count == numVertices)
    {
        for(k = 0; k < numVertices -1 ; k++)
        {
            printf("%d %d %d\n", arvoreMinima[k][0], arvoreMinima[k][1], matrizPesoAux[arvoreMinima[k][0]][arvoreMinima[k][1]]);
        }
    printf("\n");
    }
   // GeraDistribuicaoEspacial("DistriEspaKruskal", teste, distancia, quantidadeAcesso, numVertices);
}

/*====================Grafo================================*/

void InicializaGrafo(ListaGrafo *lista)
{
	lista->primeiro = (Apontador)malloc(sizeof(Grafo));
	lista->ultimo = lista->primeiro;
	lista->primeiro->matrizAdjacencia = NULL;
	lista->primeiro->numArestas = 0;
	lista->primeiro->numVertices = 0;
	lista->primeiro->proximo = NULL;

}

void LeEntrada(ListaGrafo *lista, int algoritmo)
{
	int numArestas, numVertices;

	/*
	 * origem = Vértice de origem
	 * destino = Vértice de destino
	 * peso = peso da aresta do vértice de origem ao vértice de destino
	 */
	int origem, destino, peso;
	scanf("%d %d", &numVertices, &numArestas);

	if(numVertices <= 0 && numArestas <= 0)
	{
		printf("Erro ao inserir quantidade de vértices e arestas");
	}
	else
	{
		InsereGrafo(lista, numArestas, numVertices, algoritmo);
		while(numArestas != 0)
		{
			scanf("%d %d %d", &origem, &destino, &peso);
			InsereAresta(lista->ultimo->matrizAdjacencia, origem, destino, peso);
			numArestas--;
			if(numArestas == 0)
			{
				scanf("%d %d", &numVertices, &numArestas);
				if(numArestas == 0)
				{
					break;
				}
				InsereGrafo(lista, numArestas, numVertices, algoritmo);
			}
		}
	}
}

int **CriaMatrizDeAdjacencia(int tamanho, int algoritmo)
{
	int **matriz;
	int i, j;
	tamanho = 2*tamanho;
	matriz = (int **)malloc(tamanho * sizeof(int *)); //Aloca as linhas da matriz

	/*
	 * Tratamento de erro. Verifica se as linhas da matriz são alocadas corretamente e/ou
	 * existe memória suficiente
	 */
	if(matriz == NULL)
	{
		printf("Matriz (linha) nao alocada. Verifique memoria\n");
		exit(1);
	}

	for(i=0; i<tamanho; i++)
	{
		matriz[i] = (int *)malloc(tamanho * sizeof(int)); //Aloca as colunas da matriz
		/*
		 * Tratamento de erro. Verifica se as colunas da matriz são alocadas corretamente e/ou
		 * existe memória suficiente
		 */
		if(matriz[i] == NULL)
		{
			printf("Matriz (coluna) nao alocada. Verifique memoria\n");
			exit(1);
		}

	}

	/*
	 * Laço para preencher a matriz. Caso o algoritmo seja de Kruskal,
	 * os valores iniciais dos pesos das arestas recebem INT_MAX (biblioteca limits.h).
	 * Caso seja o algoritmo seja de Prim, o vetor é preenchido com o valor inteiro 0
	 */
	for(i=0; i<tamanho; i++)
	{
		for(j=0; j<tamanho; j++)
		{
			if(algoritmo == 1) matriz[i][j] = 0;
			else if (algoritmo == 2) matriz[i][j] = INT_MAX;
		}
	}

	return matriz;
}

void InsereGrafo(ListaGrafo *lista, int numArestas, int numVertices, int algoritmo)
{
	Apontador aux = lista->ultimo;
	aux->proximo = (Apontador)malloc(sizeof(Grafo));
	aux = aux->proximo;
	aux->numArestas = numArestas;
	aux->numVertices = numVertices;
	aux->matrizAdjacencia = CriaMatrizDeAdjacencia(numVertices, algoritmo);
	aux->proximo = NULL;
	lista->ultimo = aux;
}

void InsereAresta(int **matriz, int origem, int destino, int peso)
{
	/*
	 * Grafo não direcionado. Devemos alocar a aresta A para os vértices (u,v) e para
	 * os vértices (v,u)
	 */
	matriz[origem][destino] = peso;
	matriz[destino][origem] = peso;
}

int MaiorPesoDeAresta(int **matriz, int numVertice)
{
	int tamanho = 0; //Inicializando com um valor sem peso
	int i, j;

	/*
	 * Matriz de adjacência sempre será quadrada, e seu lado terá o tamanho de
	 * (unidades) do número de vértices.
	 */
	for(i=0; i<numVertice; i++)
	{
		for(j=0; j<numVertice; j++)
		{
			if(tamanho < matriz[i][j]) tamanho = matriz[i][j];
		}
	}

	return tamanho;
}

void GeraSaidaPadrao(ListaGrafo *lista, int algoritmo)
{
	Apontador aux = lista->primeiro->proximo;
	int cont = 1;

	while(aux != NULL)
	{
		printf("Teste %d\n", cont);
		//if(algoritmo == 1) Prim(aux->matrizAdjacencia, aux->numVertices, aux->numArestas, cont);
		if(algoritmo == 2) Kruskal(aux->matrizAdjacencia, aux->numVertices, aux->numArestas, cont);
		else
		{
			printf("Erro no parametro para escolha do algoritmo\n");
			exit(1);
		}
		aux = aux->proximo;
		cont++;
	}
}


void LiberaGrafo(ListaGrafo *lista)
{
	Apontador aux, apaga;
	aux = lista->primeiro;

	while(aux != NULL)
	{
		apaga = aux;
		aux = aux->proximo;
		apaga->matrizAdjacencia = LiberaMatrizDeAdjacencia(apaga->matrizAdjacencia, apaga->numVertices);
		free(apaga);
	}
}

int **LiberaMatrizDeAdjacencia(int **matriz, int tamanho)
{
	  int  i;
	  if(matriz == NULL) return (NULL);

	  for(i=0; i<tamanho; i++)
	  {
		  free(matriz[i]);
	  }
	  free (matriz);
	  return (NULL);
}

int main(int argc,char *argv[])
{
	ListaGrafo lista;
	InicializaGrafo(&lista);
	LeEntrada(&lista, 2);
	GeraSaidaPadrao(&lista, 2);
	LiberaGrafo(&lista);
	printf("FIM\n");
	return 0;
}
