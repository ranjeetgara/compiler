#include <stdbool.h>


extern void insert(char lexeme[], char attribute[]);

extern void display(void);

extern void input(bool left, bool middle, bool right);

extern char buffer1[65], buffer2[65], buffer3[65], *forward;

extern int file_dcs;

struct node
{
    char *lexeme;
    char attribute[32];
    struct node *next;
};

typedef struct node token;

extern token *head;

extern void tokenize(void);

extern char getnext(void);

extern void putback(void);

extern bool is_keyword(char word[]);

extern char escape_char(char);