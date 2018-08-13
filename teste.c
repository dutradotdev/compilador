/*
 * match.c
 *
 * Este programa simplesmente testa se uma expressão regular casa (match)
 * com uma entrada (input).
 *
 * argv[1] = expressão regular
 * argv[2] = input
 *
 * ex: ./match '^12' '1234567890'
 */

/* headers necessários */
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

/* recebe como parâmetro a expressão regular e o input para
 * tentar casar */
void er_match(char* argv)
{
regex_t reg;

     //compilo 
     if(regcomp(&reg, "^[a-zA-Z][a-zA-Z0-9]", REG_EXTENDED|REG_NOSUB) != 0) {
         printf("erro ao compilar");
         exit(1);
     }
     
     if((regexec(&reg, argv, 0, (regmatch_t *)NULL, 0)) == 0) {
         printf("casou");
     } else {
         printf("nao casou");
     }
}

int main(int argc, char **argv)
{
    char *string="lucas";
	er_match(string);
	return 0;
}