#include 
#include 

/*Criando variáveis para fazer a validação das informações*/
int num=0;
int natacao=0;
int hidroginastica=0;
int ginasticaAerobica=0;
int ginasticaLocalizada=0;
int musculacao=0;
int artesMarciais=0;
int msgMusculacao=0;


int main (void) {

printf ("RELATORIO DA ACADEMIA: \n\n\n");

/*Questionário para o cliente preencher onde a cada resposta eu vou adicionando pontos ou não de acordo com a resposta do cliente*/

printf ("MELHORAR SISTEMA CARDIO RESPIRATORIO? \n\n");
printf ("Digite (1) para sim e (0)para nao: ");
scanf ("%d",&num);
if (num==1){
natacao++;
ginasticaAerobica++;
}
num = 0;
printf ("\n\n");
printf ("OBTER FORCA? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
natacao++;
hidroginastica++;
musculacao++;
}
num = 0;
printf ("\n\n");
printf ("OBTER RESISTENCIA? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
natacao++;
musculacao++;
}
num = 0;
printf ("\n\n");
printf ("OBTER COORDENACAO? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
natacao++;
hidroginastica++;
artesMarciais++;
}
num = 0;
printf ("\n\n");
printf ("COMPETIR? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
natacao++;
artesMarciais++;
}
num = 0;
printf ("\n\n");
printf ("MELHORAR A ARTICULACAO? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
hidroginastica++;
ginasticaAerobica++;
}
num = 0;
printf ("\n\n");
printf ("MELHORAR O CONDICIONAMENTO FISICO? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
ginasticaAerobica++;
musculacao++;
artesMarciais++;
}
num = 0;
printf ("\n\n");
printf ("MELHORAR ESTETICAMENTE? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
musculacao++;
}
num = 0;
printf ("\n\n");
printf ("PERDER GORDURA CORPORAL? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
musculacao++;
}
num = 0;printf ("\n\n");
printf ("ADQUIRIR DISCIPLINA? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
artesMarciais++;
}
num = 0;
printf ("\n\n");
printf ("APRENDER PRINCIPIOS DE ETICA? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
artesMarciais++;
}
num = 0;
printf ("\n\n");
printf ("VOCE TEM ALGUM PROBLEMA RESPIRATÓRIO? \n\n");
printf ("Digite (1) para sim e (0) para nao: ");
scanf ("%d",&num);
if (num==1){
natacao++;
}
num = 0;
printf ("\n\n");
printf ("QUANTOS ANOS VOCE? \n\n");
scanf ("%d",&num);
if(numhidroginastica)&&(natacao>ginasticaAerobica)&&(natacao>ginasticaLocalizada)&&(natacao>musculacao)&&(natacao>artesMarciais)){
printf ("AULA INDICADA: NATACAO\n\n");
}
else if ((hidroginastica>natacao)&&(hidroginastica>ginasticaAerobica)&&(hidroginastica>ginasticaLocalizada)&&(hidroginastica>musculacao)&&(hidroginastica>artesMarciais)){
printf ("AULA INDICADA: HIDROGINASTICA\n\n");
}
else if ((ginasticaAerobica>natacao)&&(ginasticaAerobica>hidroginastica)&&(ginasticaAerobica>ginasticaLocalizada)&&(ginasticaAerobica>musculacao)&&(ginasticaAerobica>artesMarciais)){
printf ("AULA INDICADA: GINASTICA AEROBICA\n\n");
}
else if ((ginasticaLocalizada>natacao)&&(ginasticaLocalizada>hidroginastica)&&(ginasticaLocalizada>ginasticaAerobica)&&(ginasticaLocalizada>musculacao)&&(ginasticaLocalizada>artesMarciais)){
printf ("AULA INDICADA: GINASTICA LOCALIZADA\n\n");
}
else if ((musculacao>natacao)&&(musculacao>hidroginastica)&&(musculacao>ginasticaLocalizada)&&(musculacao>ginasticaAerobica)&&(musculacao>artesMarciais)){
printf ("AULA INDICADA: MUSCULACAO\n\n");
if (msgMusculacao==1){
printf ("* AULADE MUSCULACAO TEM ACOMPANHAMENTO ESPECIAL, COM FINALIDADE FISIOTERAPEUTICA\n\n"); 
} 
}
else if ((artesMarciais>natacao)&&(artesMarciais>hidroginastica)&&(artesMarciais>ginasticaAerobica)&&(artesMarciais>musculacao)&&(artesMarciais>ginasticaLocalizada)){
printf ("AULA INDICADA: ARTES MARCIAIS\n\n");
}
else if (natacao==hidroginastica==ginasticaAerobica==ginasticaLocalizada==musculacao==artesMarciais){
printf ("AULA INDICADA: NATACAO, HIDROGINASTICA, GINASTICA AEROBICA, GINASTICA LOCALIZADA, MUSCULACAO E ARTES MARCIAIS\n\n");
if (msgMusculacao==1){
printf ("* AULA DE MUSCULACAO TEM ACOMPANHAMENTO ESPECIAL, COM FINALIDADE FISIOTERAPEUTICA\n\n"); 
} 
}
else if (natacao=hidroginastica==ginasticaAerobica==ginasticaLocalizada==musculacao){
printf ("AULA INDICADA: NATACAO, HIDROGINASTICA, GINASTICA AEROBICA, GINASTICA LOCALIZADA E MUSCULACAO\n\n"); 
if (msgMusculacao==1){
printf ("* AULA DE MUSCULACAO TEM ACOMPANHAMENTO ESPECIAL, COM FINALIDADE FISIOTERAPEUTICA\n\n"); 
} 
}
else if (hidroginastica=ginasticaAerobica==ginasticaLocalizada==musculacao==artesMarciais){
printf ("AULA INDICADA: HIDROGINASTICA, GINASTICA AEROBICA, GINASTICA LOCALIZADA, MUSCULACAO E ARTES MARCIAIS\n\n");
if (msgMusculacao==1){
printf ("* AULA DE MUSCULACAO TEM ACOMPANHAMENTO ESPECIAL, COM FINALIDADE FISIOTERAPEUTICA\n\n"); 
} 
}
else if (natacao==hidroginastica==ginasticaLocalizada==musculacao==artesMarciais){
printf ("AULA INDICADA: NATACAO, HIDROGINASTICA, GINASTICA LOCALIZADA, MUSCULACAO E ARTES MARCIAIS\n\n");
if (msgMusculacao==1){printf ("* AULA DE MUSCULACAO TEM ACOMPANHAMENTO ESPECIAL, COM FINALIDADE FISIOTERAPEUTICA\n\n"); 
} 
}
else if (natacao=hidroginastica==ginasticaAerobica==musculacao==artesMarciais){
printf ("AULA INDICADA: NATACAO, HIDROGINASTICA, GINASTICA AEROBICA, MUSCULACAO e ARTES MARCIAIS\n\n"); 
if (msgMusculacao==1){
printf ("* AULA DE MUSCULACAO TEM ACOMPANHAMENTO ESPECIAL, COM FINALIDADE FISIOTERAPEUTICA\n\n"); 
} 
}
else if (natacao=hidroginastica==ginasticaAerobica==ginasticaLocalizada==artesMarciais){
printf ("AULA INDICADA: NATACAO, HIDROGINASTICA, GINASTICA AEROBICA, GINASTICA LOCALIZADA e ARTES MARCIAIS\n\n"); 
}
/* Vamos fazendo a condição else if até chegar as variáveis em que sobrar apenas dois tipos de aulas com somatória iguais*/
else if (natacao=hidroginastica){
printf ("AULA INDICADA: NATACAO E HIDROGINASTICA\n\n"); 
}


printf("Siga uma dieta balanceada com 50 a 60% de carboidratos, 15 a 30% de proteínas e o restante de gorduras\n\n " );
system ("PAUSE");
}

