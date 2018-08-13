
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   analisador.h
 * Author: lucas
 *
 * Created on March 25, 2018, 11:53 PM
 */


#ifndef STDLIBLIST_H
#define STDLIBLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>
 bool verifica_se_numero(char value){
    	switch(value){
    		case '0':
    			return true;
    			break;
    		case '1':
    			return true;
    			break;
    		case '2':
    			return true;
    			break;
    		case '3':
    			return true;
    			break;
    		case '4':
    			return true;
    			break;
    		case '5':
    			return true;
    			break;
    		case '6':
    			return true;
    			break;
    		case '7':
    			return true;
    			break;	
    		case '8':
    			return true;
    			break;
    		case '9':
    			return true;
    			break;
    		default:
    			return false;
    	}
 }
 
 bool verifica_se_operador(char value){
     switch(value){
         case '+':
             return true;
             break;
         case '-':
             return true;
             break;
         case '*':
             return true;
             break;
         case '=':
             return true;
             break;             
         default: return false;
     }
 }
 
 bool verifica_se_parenteses(char value){
     switch(value){
         case '(':
             return true;
             break;
         case ')':
             return true;
             break;
         default: return false;
     }
 }

bool verifica_se_end_of_statement(char value){
     switch(value){
         case ';':
             return true;
             break;
         default: return false;
     }
 }

 bool verifica_se_palavra(char* string) {
     regex_t reg;
     //compilo 
     if(regcomp(&reg, "^[a-zA-Z][a-zA-Z0-9]", REG_EXTENDED|REG_NOSUB) != 0) {
         printf("erro ao compilar");
         exit(1);
     }
     
     if((regexec(&reg, string, 0, (regmatch_t *)NULL, 0)) == 0) {
         return true;
     } else {
         return false;
     }
 }

 bool verifica_se_letra(char string) {
     regex_t reg;
     //compilo 
     if(regcomp(&reg, "[a-zA-Z]", REG_EXTENDED|REG_NOSUB) != 0) {
         printf("erro ao compilar");
         exit(1);
     }

     if((regexec(&reg, &string, 0, (regmatch_t *)NULL, 0)) == 0) {
         return true;
     } else {
         return false;
     }
 }

char getTipoChar(char value){
    if(verifica_se_numero(value)){
        return 'N';
    }else if(verifica_se_operador(value)){
        return 'O';
    }else if(verifica_se_parenteses(value)){
        return 'P';
    }else if(verifica_se_end_of_statement(value)){
        return 'E';
    }else{
        return 'X';
    }
}

void padraoLista(char value){
    if(verifica_se_numero(value)){
        return 'N';
    }else if(verifica_se_operador(value)){
        return 'O';
    }else if(verifica_se_parenteses(value)){
        return 'P';
    }else if(verifica_se_end_of_statement(value)){
        return 'E';
    }else{
        return 'X';
    }
}

void append(char* s, char c){
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
#ifdef __cplusplus
}
#endif

#endif