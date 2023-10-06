#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <ncurses.h>

typedef struct linha LINE;

char separarLinhas(char *str, char lines[][100], int *num_lines);

void handleQuery( DATA d, int query);

void criaMenu();

//void addpagina(WINDOW **paginas, WINDOW *win, int paginaatual);

//WINDOW *criaQueryWindow();



#endif