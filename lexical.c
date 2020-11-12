#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

#ifndef LEX_FUNC_C_INCLUDED
#define LEX_FUNC_C_INCLUDED
    #include "lex_func.c"
#endif      // lex_func.c is included....

#ifndef LEX_IO_C_INCLUDED
#define LEX_IO_C_INCLUDED
    #include "lex_io.c"
#endif     // lex_io.c is included....


#ifndef LEXICAL_H_INCLUDED
#define LEXICAL_H_INCLUDED
    #include "lexical.h"
#endif       //lexical.h is included.....



int main(){
     
    file_dcs = open("input.txt", O_RDONLY);
    if (file_dcs < 0 ){

        printf("Unable to open file hai\n");
        exit(0);    

    }
    
    
    input(true, false, false);
    tokenize();
    display();
    return 0;

}