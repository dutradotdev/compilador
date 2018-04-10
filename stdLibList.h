/* 
 * File:   stdLibList.h
 * Author: lucas
 *
 * Created on March 25, 2018, 11:53 PM
 */
#define STDLIBLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* deixei alguns em pt-br para não gerar tanta confusão */
typedef struct node{
  int endereco;
  char lexema[20];
  char *token;
  char *padrao; 
  char *ocorrencia;
  struct node* next;
}Node;
    
/* 
 * Função que inicializa uma lista vazia 
 * Como ela não tem elementos, logo não há próximos elementos e por padrão ela um ponteiro
 * elemento_tabela NULL
 */
Node* initialize(void){
    return NULL;
}                   

/*
 * Função de inserção
 * Para cada elemento na lista, a gente aloca dinâmicamente a memória necessária para armazenar
 * o elemento e encadeálo na lista existente. 
 * Como a lista deve ter seu valor atualizado, ela recebe como parâmetro a lista onde será inserido o 
 * elemento e o próprio elemento e retorna a nova lista. No caso, um ponteiro para o elemento inserido.
 * Nesse caso, vamos inserir no fim da lista
 */

Node* insert(Node* actualList, char lexema[], char token[], char padrao[], char ocorrencia[]){
    Node* newNode = (Node*) malloc(sizeof(Node));
    
    if(newNode == NULL){
        printf("Nao foi possivel criar o no da lista");
        exit(-1);
    }
    
    strcpy(newNode -> lexema, lexema);
    newNode -> token = token;
    newNode -> padrao = padrao;
    newNode -> ocorrencia = ocorrencia;
    newNode -> next = NULL; //pq é o último node
   
    //Se o actualList for null é porque não há elementos, logo esse será o primeiro elemento
    if(actualList == NULL){
       actualList = newNode;
    } else {
       Node* current = actualList;
       //Caso já tenho elementos, eu clono a minha lista atual (por causa dos undefined behaviors) e enquanto meu elemento next não for null (ultimo elemento da lista)
       //eu atribuo o next até ser null
       while(current -> next != NULL){
         current = current -> next;
       };
       
       current -> next = newNode;
    }
    printf("\ninsert fim:%s\n", lexema);
    return actualList;
}


/*
 * Função que imprime todos os elementos da lista 
*/
void printList(Node* list){
	Node* aux_list = list;
	
    int cont = 0;
    do{
        printf("\n================================================\n");
        printf("Endereco: %d\n", cont);
        printf("Lexema: %s\n", aux_list->lexema);
        printf("Token: %s\n", aux_list -> token);
        printf("Padrao: %s\n", aux_list -> padrao);
        printf("Ocorrencia: %s\n", aux_list -> ocorrencia);
        printf("================================================\n");

        //Trecho que imprime no arquivo tabela_simbolos

        FILE *file;
        file = fopen("D:\\workspace\\compilador\\tabela_simbolos.txt" , "a");

        if (file == NULL) {
            printf ("Arquivo nao pode ser aberto!");
            getchar();
            exit (1);

        }

        fprintf(file, "\n================================================\n");
        fprintf(file, "Endereco: %d\n", cont);
        fprintf(file, "Lexema: %s\n", aux_list->lexema);
        fprintf(file, "Token: %s\n", aux_list -> token);
        fprintf(file, "Padrao: %s\n", aux_list -> padrao);
        fprintf(file, "Ocorrencia: %s\n", aux_list -> ocorrencia);
        fprintf(file, "================================================\n");

        fclose(file);


        //Trecho que imprime no arquivo token

        FILE *file2;
        file2 = fopen("D:\\workspace\\compilador\\token.txt" , "a");

        if (file2 == NULL) {
            printf ("Arquivo nao pode ser aberto!");
           getchar();
           exit (1);

        }

                fprintf(file2, "< ");
        fprintf(file2, "%s", aux_list -> token);
        fprintf(file2, ", %d", cont);
        fprintf(file2, ">; ");

        fclose(file2);

        cont++;
        aux_list = aux_list -> next;
    }while(aux_list != NULL);    
}
