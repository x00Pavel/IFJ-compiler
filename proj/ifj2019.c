#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "errors.h"
#include "scaner.h"

// je nutne udelat v headeru prototipy

void scaner(char *str, token_ptr ptr){
int c;
	for( int i = 0; (c = getchar()) != ' ' || c != '\n' || c != EOF ; i++)
	{
	str[i] = c;
	}
	check(str, &c, ptr);
	//scaner(str);
}

void check(char *str, int *c, token_ptr ptr){
for( int i = 0; i < 7; i++){ // analogicke funcke pro ostatni typy atributu
	if(strcmp(*str,*key_word_arr[i])){
		create_token_kw(str, ptr, &i); // sem pridame funcki pro vytvoreni tokenu
		}
	}
for( int  i = 0; i < 22; i++){
	if(strcmp(*str,"+")){
		ptr -> type = TOKEN_SUM;
		ptr -> attribute = NULL; // muzene vynechat
	}
	if(strcmp(*str,"*")){
		ptr -> type = TOKEN_MULTIPLY;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,"/")){
		ptr -> type = TOKEN_DIVISION;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,"=")){
		ptr -> type = TOKEN_ASSIGN;
		ptr -> attribute = NULL; // muzene vynechat
	}
	if(strcmp(*str,"==")){
		ptr -> type = TOKEN_EQUAL;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,"!=")){
		ptr -> type = TOKEN_NOT_EQUAL;
		ptr -> attribute = NULL;
	}
		if(strcmp(*str,">")){
		ptr -> type = TOKEN_GREATER;
		ptr -> attribute = NULL; // muzene vynechat
	}
	if(strcmp(*str,"<")){
		ptr -> type = TOKEN_LESS;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,">=")){
		ptr -> type = TOKEN_GREATER_EQ;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,"<=")){
		ptr -> type = TOKEN_LESS_EQ;
		ptr -> attribute = NULL; // muzene vynechat
	}
	if(strcmp(*str,"EOF")){
		ptr -> type = TOKEN_EOF;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,"\n")){
		ptr -> type = TOKEN_EOL;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str," ")){
		ptr -> type = TOKEN_EMPTY;
		ptr -> attribute = NULL; // muzene vynechat
	}
	if(strcmp(*str,"(")){
		ptr -> type = TOKEN_L_BRACKET;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,")")){
		ptr -> type = TOKEN_R_BRACKET;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,".")){
		ptr -> type = TOKEN_DOT;
		ptr -> attribute = NULL; // muzene vynechat
	}
	if(strcmp(*str,",")){
		ptr -> type = TOKEN_COMA;
		ptr -> attribute = NULL;
	}
	if(strcmp(*str,";")){
		ptr -> type = TOKEN_SEMICOLON;
		ptr -> attribute = NULL;
	}
	//at , asi podarzi se nam tento kus kodu zoptimizovat
	
}	
	//if(c != EOF){ // kdyz nejsme na konci souboru, tak hledame dalsi slovo
	//scaner(str);
	//} // dalsi slovo bude hledat PARSER
}

void create_token_kw(char *str, token_ptr ptr, int *i){
	ptr -> type = TOKEN_KEY_WORD;
	ptr -> attribute.key_word = i;
}

int main(int arc, char **argv)
{
	char str[50];
    /* Input file */
    FILE *file;
    file = fopen(argv[0], "r");
    if (!file){
        fprintf(stderr, "Error in opening file %s\n", argv[0]);
        return ERR_OTHER;
    }
    /* Lexer */
    token_ptr ptr;
    	scaner(str, ptr);
    fclose(file);
    /* Syntax analyzer MAIN PROCESS */

    /* Semantic analyzer */

    /* Intermediate code generator */

    /* Optimizer */

    /* Code generator */

}
