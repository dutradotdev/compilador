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
    char str[25];
    memset(&str[0], 0, sizeof(str));
    int contador_de_linha, contador_de_coluna, contador_de_caract;
    int i = 0;
    
    typedef struct node{
        char endereco[20];
        char lexema[20];
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
       int str_len = strlen(str);
       str_len++;
       char new_str[str_len];
       memset(&new_str[0], 0, sizeof(new_str));

       //crio um outro array limpo(new_str) com apenas os elementos necessários.
       for(i = 0; i < str_len; i++){
           if(!isspace(str[i]) || verifica_se_numero(str[i]) || verifica_se_operador(str[i]) || verifica_se_parenteses(str[i]) || verifica_se_end_of_statement(str[i]) || verifica_se_letra(str[i])){
               char c = str[i];
               append(new_str, c);
           }
       }
       
       /*
       * Na string, eu vou ter a sequencia de caracteres. No for, eu pego o caracter atual e o caracter anterior da string.
       * Se eles tiverem o mesmo tipo, (se ambos forem number ou ambos forem parenteses ou sei lá) eu concateno eles em uma string
       * pois ambos fazer parte do mesmo token. Essa string(str_cmp) é o lexema. 
       * Quando o tipo do caracter atual for diferente do anterior, significa que o lexema mudou.
       * Aí eu pego o tipo do lexema atual que está na str_cmp (number, end_of_st..) e adiciono na lista.
       * Aí eu reseto a str_cmp pro próximo lexema.
       */
       char lexema[20];
       char aux_lexema[20];
       memset(&lexema[0], 0, sizeof(lexema));
       memset(&aux_lexema[0], 0, sizeof(aux_lexema));
       contador_de_caract = 0;
       
       for(i = 0; i <= str_len; i++){
          char atual = new_str[i];
          char anterior = i == 0 ? "" : new_str[i-1];
          contador_de_caract++;

          if(i ==0 || i == 1){
             append(lexema, atual);
          }
               
          if(i > 1 && getTipoChar(atual) == getTipoChar(anterior)){
              append(lexema, atual);
          }else if(i > 1 && getTipoChar(atual) != getTipoChar(anterior)){
              strcpy(aux_lexema, lexema);          
              if(verifica_se_numero(anterior)){
                  no = insert(no, aux_lexema, "NUMBER", "Numeros seguidos de numeros.", "1");
              }else if(verifica_se_operador(anterior)){
                  no = insert(no, aux_lexema, "OPERATOR", "Operadores.", "1");
              }else if(verifica_se_parenteses(anterior)){              	
                  no = insert(no, aux_lexema, "PARENTESES", "Abertura ou fechamento de parenteses().", "1");
              }else if(verifica_se_palavra(lexema)){
                  no = insert(no, aux_lexema, "PALAVRA", "Variavel ou palavra reservada.", "1");
              }else{            	
                  no = insert(no, aux_lexema, "END_OF_STATEMENT", ";", "1");
              }
			  
              memset(&lexema[0], 0, sizeof(lexema));
              append(lexema, atual);
           }
       }
       memset(&new_str[0], 0, sizeof(new_str));
	}

	printList(no);   
    fclose(file);
    return 0;
}
