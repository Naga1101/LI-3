#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datastruc.h"
#include "loadfiles.h"
#include "query.h"
#include "batch.h"
#include "interactive.h"
#include "func.h"

int main(int argc, char *argv[]) {
    DATA d;

    if (argc == 1){
        initscr();
        cbreak();
        curs_set(0);
        keypad(stdscr, TRUE);

        criaMenu();

        endwin();
    }
    else {
        d = load(argv[1]);
        batch(d, argv[2]);
        cleanStruct(d);
    }
    //printf("\n\t-- End --  \n");

    return 0; 
}
