#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef LEX_IO_C_INCLUDED
#define LEX_IO_C_INCLUDED
    #include "lex_io.c"
#endif     // lex_func.c is included....


#ifndef LEXICAL_H_INCLUDED
#define LEXICAL_H_INCLUDED
    #include "lexical.h"
#endif       //lexical.h is included.....



token *head;


bool is_keyword(char word[])          // Checks for reserved words
{
    char keywords[32][10] = {   "auto",	"double",	"int",	"struct",
                                "break",	"else",	"long",	"switch",
                                "case",	"enum",	"register",	"typedef",
                                "char",	"extern",	"return",	"union",
                                "const",	"float",	"short",	"unsigned",
                                "continue",	"for",	"signed",	"void",
                                "default",	"goto",	"sizeof",	"volatile",
                                "do",	"if",	"static",	"while" };
    int i = 0;
    for(i = 0; i < 32; i++){
        if (strcmp(word, keywords[i]) == 0){
            return true;
        }
    }
    return false;

}

char escape_char(char ch){          // checks for escape character.

    if(ch == 'a'){
        return '\a';
    }
    else if (ch == 'b'){
        return '\b';
    }
    else if (ch == 'f'){
        return '\f';
    }
    else if (ch == 'n'){
        return '\n';
    }
    else if (ch == 'r'){
        return '\r';
    }
    else if (ch == 't'){
        return '\t';
    }
    else if (ch == 'v'){
        return '\v';
    }
    else if (ch == '\\'){
        return '\\';
    }
    else if (ch == '\''){
        return '\'';
    }
    else if (ch == '"'){
        return '\"';
    }
    else if (ch == '?'){
        return '\?';
    }
    else if (ch == '0'){
        return '\0';
    }
    else{
        return ch;
    }

}

void insert(char lexeme[], char attribute[])           // inserts the lexeme into linked list wiht its attribute.
{

    token *temp1, *temp2;
    temp1 = head;

    if (temp1 == NULL){

        head = (token*) malloc(sizeof(token));
        head->lexeme = (char *)malloc(sizeof(char) * strlen(lexeme));
        strcpy(head->lexeme, lexeme);
        strcpy(head->attribute, attribute);

    }
    else{

        while(temp1->next != NULL){

        temp1 = temp1->next;

        }
        
        temp1->next = (token*) malloc(sizeof(token));
        temp1 = temp1->next;
        temp1->lexeme = (char *)malloc(sizeof(char) * strlen(lexeme));
        strcpy(temp1->lexeme, lexeme);
        strcpy(temp1->attribute, attribute); 

    }

    return;

}


void tokenize()                                 // recocgnizes tokens and keywords.
{
    char *buff = NULL, ch;
    int i = -1, state = 0;


/*
OP_BRCS = open Braces  {
CL_BRCS = close Braces }
OP_PRA = open paranthesis (
CL_PRA = close paranthesis )
PNCTION = punctuations . , ? : ; -> \
BTOPRTR = bitwise operator ^ ~ & | >> << 
LGOPRTR = logical operator  && || !
RLOPRTR = relational operator >= > <= < != ==
AROPRTR = arthematic operator * + % - /
INCRMT = increment ++
DNCRMT = decrement -- 
ASIMNT = assignment operator =
NUM = intergers
FLOAT = real numbers
CHAR = charecters
STRNG = strings
*/    
    do
    {
        ch = getnext();
        switch (state)
        {
            case 0:
                if (ch == ' ' && buff == NULL){             // checks wether space is a part of string or charecter.
                    continue;
                }
                else if (ch == '{'){
                    insert("{","OP_BRCS");
                }
                else if (ch == '}'){
                    insert("}","CL_BRCS");
                }
                else if (ch == '('){
                    insert("(", "OP_PRA");
                }
                else if (ch == ')'){
                    insert(")","CL_PRA");
                }
                else if (ch == '['){
                    insert("[","OP_BRKT");
                }
                else if (ch == ']'){
                    insert("]","CL_BRKT");
                }

                else if (ch == '.'){        
                    ch = getnext();
                    if(ch >= '0' && ch <= '9'){                     // checks wether . is part of  float ( ex: .26)
                        if(buff == NULL && (i = -1)){
                            buff = (char *)malloc(sizeof(char)*32);
                        }
                        buff[++i] = '.';
                        buff[++i] = ch;
                        state = 2;
                    }
                    else{                                           // if not returns the extra char read.
                        putback();
                        insert(".", "PNCTION");
                    }
                    
                }
                else if (ch == ','){
                    insert(",", "PNCTION");
                }
                else if (ch == '\\'){
                    insert("\\", "PNCTION");
                }
                else if (ch == '?'){
                    insert("?", "PNCTION");
                }
                else if (ch == ';'){
                    insert(";", "PNCTION");
                }
                else if (ch == ':'){
                    insert(":", "PNCTION");
                }

                else if (ch == '^'){
                    insert("^", "BTOPRTR");
                }
                else if (ch == '~'){
                    insert("~", "BTOPRTR");
                }
                else if (ch == '&'){             // checks for the logical '&&' or bitwiese '&'
                    ch = getnext();
                    if (ch == '&'){
                        insert("&&", "LGOPRTR");
                    }
                    else{
                        putback();
                        insert("&", "BTOPRTR");
                    }
                }
                else if (ch == '|'){            // check for the logical '||' or bitwise '||'
                    ch = getnext();
                    if (ch == '|'){
                        insert("||","LGOPRTR");
                    }
                    else{
                        putback();
                        insert("|", "BTOPRTR");
                    }
                }
                else if (ch == '>'){             // checks for bitwise '>>' or relational '>=' or '>'
                    ch = getnext();
                    if (ch == '>'){
                        insert(">>","BTOPRTR");
                    }
                    else if (ch == '='){
                        insert(">=", "RLOPRTR");
                    }
                    else{
                        putback();
                        insert(">","RLOPRTR");
                    }
                }
                else if (ch == '<'){            // checks for bitwise '<<' or relational '<=' or '<'
                    ch = getnext();
                    if (ch == '<'){
                        insert("<<", "BTOPRTR");
                    }
                    else if (ch == '='){
                        insert("<=", "RLOPRTR");
                    }
                    else{
                        putback();
                        insert("<","RLOPRTR");
                    }
                }
                else if (ch == '!'){             // checks for logical ! or relational !=
                    ch = getnext();
                    if (ch == '='){
                        insert("!=", "RLOPRTR");
                    }
                    else{
                        putback();
                        insert("!", "LGOPRTR");
                    }
                    
                }

                else if (ch == '*'){
                    insert("*", "AROPRTR");
                }

                else if (ch == '+'){             // checks for arthematic '+' or increment '++'                          
                    ch = getnext();
                    if (ch == '+'){
                        insert("++", "INCRMT");
                    }
                    else{
                        putback();
                        insert("+", "AROPRTR");
                    }
                }

                else if(ch == '%'){
                    insert("%", "AROPRTR");
                }                

                else if(ch == '-'){               // checks for arthematic '-' or  decrement '--' or punctuation '->'
                    ch = getnext();
                    if (ch == '-'){
                        insert("--","DNCRMT");
                    }
                    else if(ch == '>'){
                        insert("->","PNCTION");
                    }
                    else{
                        putback();
                        insert("-","AROPRTR");
                    }
                }

                else if(ch == '/'){               // checks for arthematic '/' or single line comment // or multi-line comment /*
                    ch = getnext();
                    if (ch == '/'){
                        state = 6;                
                    }
                    else if (ch == '*'){
                        state = 7;
                    }
                    else{
                        putback();
                        insert("/", "AROPRTR");
                    }
                }
                else if (ch == '='){              // checks for relational '==' or asignment '='
                    ch = getnext();
                    if (ch == '='){
                        insert("==", "RLOPRTR");
                    }
                    else{
                        insert("=","ASIMNT");
                        putback();
                    }
                }
                else if(ch >= '0' && ch <= '9'){        // checks for number.
                    state = 1;
                    if(buff == NULL && (i = -1)){
                        buff = (char *)malloc(sizeof(char)*32);
                    }
                    buff[++i] = ch;
                }
                else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == '_')){   // checks for identifier
                    state = 4;
                    if(buff == NULL && (i = -1)){
                        buff = (char *)malloc(sizeof(char)*32);
                    }
                    
                    buff[++i] = ch;
                } 

                else if (ch == '\''){   //checks for charecter
                    state = 8;
                }

                else if(ch == '"'){     //checks for string
                    state = 9;
                }

                break;
            case 1:
                if (ch >= '0' && ch <= '9'){       //differentiates b/w integers and real values
                    buff[++i] = ch;       
                }
                else if (ch == '.'){
                    state = 2;
                    buff[++i] = ch;
                }
                else{
                    buff[++i] = '\0';
                    insert(buff, "NUM");
                    putback();
                    free(buff);
                    buff = NULL;
                    state = 0;
                }
                break;

            case 2:                                  // real values 
                if (ch >= '0' && ch <= '9'){
                    buff[++i] = ch;
                }
                else if(ch == 'E'){
                    buff[++i] = ch;
                    state = 3;
                } 
                else{
                    insert(buff, "FLOAT");
                    state = 0;
                    if(ch != ' '){
                        putback();
                    }
                    buff = NULL;
                    

                }
                break;

            case 3:                                         // real values in exponential representation
                if (ch >= '0' && ch <= '9'){
                    buff[++i] = ch;
                }
                else{
                    if(ch != ' '){
                        putback();
                    }
                    insert(buff, "FLOAT");
                    i = -1;
                    free(buff);
                    buff = NULL;
                    state = 0;
                }
                break;

            case 4:                                          //identifires which only containg alphabets
                if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_')){
                    buff[++i] = ch;
                } 
                else if (ch >= '0' && ch <= '9') {             // if it encouter a digit changes state.. 
                    buff[++i] = ch;
                    state = 5;
                }
                else{
                    if(ch != ' '){
                        putback();
                    }
                    state = 0;
                    buff[++i] = '\0';
                    if(is_keyword(buff)){
                        insert(buff, "KEYWORD");             //checks wether the identifier is a keyword 
                        free(buff);
                        buff = NULL;
                    }
                    else{
                        insert(buff, "ID");
                        free(buff);
                        buff = NULL;
                    }
                }
                break;

            case 5:                                         // identifiers wich has digits in them which canot be a keyword
                if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_') || (ch >= '0' && ch <= '9')){
                    buff[++i] = ch;
                }
                else{
                    if(ch != ' '){
                        putback();
                    }
                    state = 0;
                    insert(buff, "ID");
                    free(buff);
                    buff = NULL;
                }
                break;
            
            case 6:                                 // checks wether ch is \n to end single line comment.
                if(ch == '\n'){                                     
                    state = 0;
                }
                break;
            
            case 7:                                // checks to terminate multi-line comment.
                if (ch == '*'){
                    ch = getnext();
                    if (ch == '/'){
                        state = 0;
                    }
                }        
            break;

            case 8:
                
                if (ch != '\''){
                    if (buff == NULL){
                        buff = (char *)malloc(sizeof(char)*2);
                        buff[1] = '\0';
                    }
                    if (ch == '\\'){
                        ch = getnext();
                        ch = escape_char(ch);
                    }
                    buff[0] = ch;
                }
                else{
                    if (buff == NULL){
                        insert("NONE", "CHAR");
                    }
                    else{
                        insert(buff, "CHAR");
                        state = 0;
                        free(buff);
                        buff = NULL;
                    }
                }
            break;


            case 9:
                if (ch != '\"'){
                    if (buff == NULL && (i = -1)){
                        buff = (char *)malloc(sizeof(char)*64);
                    }
                    if (ch == '\\'){
                        ch = getnext();
                        ch = escape_char(ch);
                    }
                    buff[++i] = ch;
                }
                else
                {
                    if (buff == NULL){
                        insert("NONE", "CHAR");
                    }
                    else
                    {
                        buff[++i] = '\0';
                        insert(buff, "STRNG");
                        state = 0;
                        buff = NULL;
                    }
                    
                }
                
            break;

            default:
                break;
        }

    }while (ch != '\0');
    
}