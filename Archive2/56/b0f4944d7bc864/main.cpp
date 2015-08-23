#include <string>
 
struct T1 {};
 
classe T2
 {int 
    mem; pública: 
    T2 () {} // "mem" não consta na lista de inicializador};
   

 
int n; // A inicialização de duas fases é feito // Na primeira fase, a inicialização de zero inicializa n para zero // Na segunda fase, a inicialização padrão não faz nada, deixando n sendo zero 
       
       
 
int principal () 
{int 
    n; // non-classe: o valor é indeterminado std :: string de s; // chamadas ctor padrão, o valor é "" (string vazia) std :: string de um [2]; // chama ctor padrão, cria duas cadeias vazias // int & r; // Erro: default-inicializar uma referência // const int n; // Erro: const tipo não-classe // const t1 T1; // Erro: tipo de classe const com implícita ctor padrão 
    T1 t1; // ok, chama implícita ctor padrão const T2 t2; // ok, chama o fornecido pelo usuário padrão ctor // t2.mem é inicializado-padrão (de valor indeterminado )}            
        
     


            
          
                      
