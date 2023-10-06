#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include "datastruc.h"
#include "query.h"
#include "interactive.h"
#include "loadfiles.h"

#define NUM_OPTIONS 9

const char *options[NUM_OPTIONS] = {
    "Query 1 - Resumo de perfil.",
    "Query 2 - Top condutores em avaliacao media.",
    "Query 3 - Top utilizadores (distancia viajada).",
    "Query 4 - Preco medio de viagens numa cidade.",
    "Query 5 - Preco medio de viagens num intervalo de tempo.",
    "Query 6 - Distancia percorrida numa cidade.",
    "Query 7 - Top condutores numa cidade.",
    "Query 8 - Viagens de condutores e utilizadores com o mesmo genero (e x anos de conta)",
    "Query 9 - Viagens em que o utilizador deu gorjeta, num intervalo de tempo.",
};

void split_lines(char *str, char lines[][100], int *num_lines) {
    int i, j, k, len;

    len = strlen(str);
    *num_lines = 1;

    // contar o número de linhas
    for(i=0; i<len; i++) {
        if(str[i]=='\n') (*num_lines)++;
    }

    // Copiar cada linha para o array
    j = 0; 
    k = 0;
    for(i=0; i<len; i++) {
        if(str[i]!='\n') {
            lines[j][k] = str[i];
            k++;
        } else {
            lines[j][k] = '\0';
            j++;
            k=0;
        }
    }
}

void criaPaginas(int n, char *output){
    int i;
    char lines[n][100];
    split_lines(output, lines, &n);
    wattron(stdscr, A_BOLD);

    int linesPerPage = getmaxy(stdscr) - 5;
    int totalLines = n;
    int totalPages = (totalLines + linesPerPage - 1) / linesPerPage;

    int paginaAtual = 0;
    int primeiraLinha = 0;
    
    while (1){
        wclear(stdscr);
        for(i = primeiraLinha; i < primeiraLinha + linesPerPage && i < totalLines - 1; i++){
            mvwprintw(stdscr, 3 + (i - primeiraLinha), 2, "%s", lines[i]);
        }

        mvwprintw(stdscr, getmaxy(stdscr) - 1, 2, "Pagina %d/%d, pressione seta esquerda/direita para navegar ou 'q' para voltar.", paginaAtual + 1, totalPages);
        wrefresh(stdscr);

        int ch = getch();
        if (ch == KEY_LEFT && paginaAtual>0){
            paginaAtual--;
            primeiraLinha = paginaAtual * linesPerPage;
            wclear(stdscr);
        } else if (ch == KEY_RIGHT && paginaAtual < totalPages - 1){
            paginaAtual++;
            primeiraLinha = paginaAtual * linesPerPage;
            wclear(stdscr);
        } else if (ch != KEY_LEFT && ch != KEY_RIGHT){
        break;
        }
    }
    wattroff(stdscr, A_BOLD);
}


void handleQuery(DATA d, int query){
    int n = 0;
    char aux[50], aux1[50], aux2[50], *output = NULL, output2[1000000];

    switch (query)
    {
        case 1:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Insira o iD / username que gostaria de consultar:\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 20);
            output = iQuery1(d, aux);
            wattron(stdscr, A_BOLD);
            mvwprintw(stdscr, 3, 1, "%s\n", output);
            wattroff(stdscr, A_BOLD);
            if (output != NULL) free(output);
            mvwprintw(stdscr, 26, 14, "Pressiona qualquer outra tecla para continuar...");
            wrefresh(stdscr);
            wgetch(stdscr);
            break;
        case 2:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Insira o numero de condutores que pretende ver:\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 10);
            n = atoi(aux);
            //char lines2[n][100];
            iQuery2(d, n, output2);
            criaPaginas(n, output2);
            break;
        case 3:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Insira o numero de utilizadores que pretende ver:\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 10);
            n = atoi(aux); 
            //char lines3[n][100];
            iQuery3(d, n, output2);
            criaPaginas(n, output2);
            break;
        case 4:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Digite a cidade que pretende consultar.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 20);
            output = iQuery4(d, aux);
            wattron(stdscr, A_BOLD);
            mvwprintw(stdscr, 3, 1, "%s\n", output);
            wattroff(stdscr, A_BOLD);
            if (output != NULL) free(output);
            mvwprintw(stdscr, 26, 14, "Pressiona qualquer outra tecla para continuar...");
            wrefresh(stdscr);
            wgetch(stdscr);
            break;
        case 5:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Digite a primeira data do intervalo.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 20);
            mvwprintw(stdscr, 4, 1, "Digite a segunda data do intervalo.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux1, 20);
            output = iQuery5(d, aux, aux1);
            wattron(stdscr, A_BOLD);
            mvwprintw(stdscr, 7, 1, "%s\n", output);
            wattroff(stdscr, A_BOLD);
            if (output != NULL) free(output);
            mvwprintw(stdscr, 26, 14, "Pressiona qualquer outra tecla para continuar...");
            wrefresh(stdscr);
            wgetch(stdscr);
            break;
        case 6:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Digite a cidade que pretende consultar.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 20);
            mvwprintw(stdscr, 4, 1, "Digite a primeira data do intervalo.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux1, 20);
            mvwprintw(stdscr, 7, 1, "Digite a segunda data do intervalo.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux2, 20);
            output = iQuery6(d, aux, aux1, aux2);
            wattron(stdscr, A_BOLD);
            mvwprintw(stdscr, 11, 1, "%s\n", output);
            wattroff(stdscr, A_BOLD);
            if (output != NULL) free(output);
            mvwprintw(stdscr, 26, 14, "Pressiona qualquer outra tecla para continuar...");
            wrefresh(stdscr);
            wgetch(stdscr);
            break; 
        case 7:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Insira o numero de condutores que pretende ver:\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 10);
            mvwprintw(stdscr, 4, 1, "Digite a cidade que pretende consultar.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux1, 20);
            n = atoi(aux); 
            iQuery7(d, n, aux1, output2);
            criaPaginas(n, output2);
            break; 
        case 8:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Insira o genero comum do utilizador e condutor:\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 10);
            mvwprintw(stdscr, 4, 1, "Insira a idade do perfil:\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux1, 20);
            n = iQuery8(d, aux[0], atoi(aux1), output2);
            criaPaginas(n, output2);
            break; 
        case 9:
            wclear(stdscr);
            mvwprintw(stdscr, 1, 1, "Digite a primeira data do intervalo.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux, 20);
            mvwprintw(stdscr, 4, 1, "Digite a segunda data do intervalo.\n\t:");
            wrefresh(stdscr);
            wgetnstr(stdscr, aux1, 20); 
            n = iQuery9(d, aux, aux1, output2);
            criaPaginas(n, output2);
            break;  
    }
}


void criaMenu(){
    int highlight = 0, option = 0;
    char caminho[200];

    keypad(stdscr, TRUE);

    mvwprintw(stdscr, 1, 1, "Escreva o caminho para o dataset que pretende:\n\t:");
    wrefresh(stdscr);
    wgetnstr(stdscr, caminho, 200);
    DATA d = load(caminho);

    box(stdscr, 0, 0);
    while (option != NUM_OPTIONS){
        wclear(stdscr);
        for (int i = 0; i<NUM_OPTIONS; i++){
            if (i == highlight) {
                wattron(stdscr, A_REVERSE);
            }
            mvwprintw(stdscr, i+1, 1, "%s", options[i]);
            wattroff(stdscr, A_REVERSE);
        }
        mvwprintw(stdscr, NUM_OPTIONS + 2, 2, "Pressione 'ENTER' para escolher uma query ou 'q' para sair.");
        wrefresh(stdscr);

        option = wgetch(stdscr);

        switch (option)
        {
        case KEY_UP:
            highlight--;
                if (highlight == -1) {
                    highlight = NUM_OPTIONS-1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == NUM_OPTIONS) {
                    highlight = 0;
                }
                break;
            case 10:
                handleQuery(d, highlight+1);
                break;
            case 'q':
                option = NUM_OPTIONS;
                wclear(stdscr);
                mvwprintw(stdscr, 1, 1, "A sair...");
                wrefresh(stdscr);
                wclear(stdscr);
                break;
        }
    }
    cleanStruct(d);
}