#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>
#include "analisador.h"
#include "stdLibList.h"

int main(void){
    FILE *file;
    char nome_arquivo[12] = "entrada.txt";
    char str[25], teste[25];
    int contador_de_linha, contador_de_coluna, contador_de_caract;
    int i = 0;
    
    typedef struct node{
        
        int endereco;
        char *lexema;
        char *token;
        char *padrao;
        char *ocorrencia;
        struct node *next;
    }Node;
		
    if((file = fopen(nome_arquivo, "r")) == NULL){
	    puts("Nao tem arquivo no diretorio");
	    exit(1);
    }
    
    Node* no = initialize();
    //enquanto nao chegar no final do arquivo
	while(!feof(file)){	
	   fgets(str, 100, file);
	   contador_de_linha++;
           
           //pego o tamanho do array e declaro um array com o tamanho certo ao invés de um tamanho estático.
           int str_len = strlen(str);
           char new_str[str_len];
           for(i = 0; i < str_len; i++){
               if(!isspace(str[i]) || verifica_se_numero(str[i]) || verifica_se_operador(str[i]) || verifica_se_parenteses(str[i]) || verifica_se_end_of_statement(str[i])){
                   //crio um outro array limpo(new_str) com apenas os elementos necessários.
                   char c = str[i];
                   append(new_str, c);
               }
           }
           
           /*
           Essa parte está meio bugada. A ideia é o seguinte:
            * Na string, eu vou ter a sequencia de caracteres. No for, eu pego o caracter atual e o caracter anterior da string.
            * Se eles tiverem o mesmo tipo, (se ambos forem number ou ambos forem parenteses ou sei lá) eu concateno eles em uma string
            * pois ambos fazer parte do mesmo token. Essa string(str_cmp) é o lexema. 
            * Quando o tipo do caracter atual for diferente do anterior, significa que o lexema mudou.
            * Aí eu pego o tipo do lexema atual que está na str_cmp (number, end_of_st..) e adiciono na lista.
            * Aí eu reseto a str_cmp pro próximo lexema.
            * no método que imprime a lista printList(no); eu devo estar comendo bola em alguma coisa pois ele identifica certo o token mas insere errado o caracter. Isto está bugado
            * Esses printfs são só pra debug
            * No if deste for abaixo, eu comecei a verificar apenas i > 1 pois antes disso ele pega um garbage sei lá daonde.... 
           */
           for(i = 0; i < str_len; i++){
               char atual = new_str[i];
               char anterior = i == 0 ? "" : new_str[i-1];
               char str_cmp[20];
               contador_de_caract++;
               
               printf("\nI:%d\n", i);
               if(i == 1){
                   append(str_cmp, atual);
               }
               if(i > 1 && getTipoChar(atual) == getTipoChar(anterior)){
                   //append(str_cmp, atual);
               }else if(i > 1 && getTipoChar(atual) != getTipoChar(anterior)){
                  /* if(verifica_lexema(anterior)){
                       no = insert(no, str_cmp, "Teste");	
                   }*/if(verifica_se_numero(anterior)){
                   		no = insert(no, str_cmp, "NUMBER", "numeros seguidos de numeros", "1");
                   }else if(verifica_se_operador(anterior)){
                       no = insert(no, str_cmp, "OPERATOR", "operadores", "1");
                   }else if(verifica_se_parenteses(anterior)){
                       no = insert(no, str_cmp, "PARENTESES", "Abertura ou fechamento de parenteses()", "1");
                   }else{
                       no = insert(no, str_cmp, "END_OF_STATEMENT", ";", "1");
                   }

                   memset(&str_cmp[0], 0, sizeof(str_cmp));
                   append(str_cmp, atual);
                   printf("\nSTR_CMP %s\n", str_cmp); 

               }
               
           }
           printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
           printList(no);
           //essa linha é essencial. Quando eu vou colocar os valores no mesmo array, ele não reseta o array direito e coloca uns lixos na próxima adição. Por isso, eu tenho
           //que resetar o array todo. (https://stackoverflow.com/questions/632846/clearing-a-char-array-c)
           memset(&new_str[0], 0, sizeof(new_str));
	}
   
    fclose(file);
	
    return 0;
}

/*
                       
                       
                        
 */
