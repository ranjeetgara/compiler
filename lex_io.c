#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef LEXICAL_H_INCLUDED
#define LEXICAL_H_INCLUDED
    #include "lexical.h"
#endif       //lexical.h is included.....

char buffer1[65], buffer2[65], buffer3[65];

char *forward = &buffer1[0];

token *head; 

int file_dcs;

void input(bool left, bool middle, bool right)
{
    int n;
    
    if (left){

        n = read(file_dcs, buffer1, 64);
        buffer1[n] = '\0';
        // strcpy(buffer1,"hai\0");
    }

    if (middle){

        n = read(file_dcs, buffer2, 64);
        buffer2[n] = '\0';
    }

    if (right){
        n = read(file_dcs, buffer3, 64);
        buffer3[n] = '\0';
        
    }

    return;
}


void display()
{
    token *temp;
    temp = head;

    while(temp != NULL){
        
        printf("(%s, %s)\n", temp->attribute, temp->lexeme);
        temp = temp->next;

    }

    return;
}


char getnext()
{
    char ch = *forward;
    forward++;
    if (*forward == '\0'){
        // if(forward >= &buffer1[0] && forward <= &buffer1[64]){
        if (forward == &buffer1[64]){
            forward = buffer2;
            input(false, false, true);
        }
        else if(forward == &buffer2[64]){ //(forward >= &buffer2[0] && forward <= &buffer2[64]){
            forward = buffer3;
            input(true, false, false);
        }     
        else if (forward == &buffer3[64]){
            forward = buffer1;
            input(false, true, false);
        }
    }
    return ch;
}

void putback(){
    
    if (forward == buffer1){
        forward = &buffer3[64];
    }

    else if (forward == buffer2){
        forward = &buffer1[64];
    }

    else if (forward == buffer3){
        forward = &buffer2[64];
    }
    else{
        forward--;
    }
    
}