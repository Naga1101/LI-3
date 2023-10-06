#include "query.h"
#include "drivers.h"
#include "datastruc.h"
#include "glib.h"
#include <stdio.h>
#include "interactive.h"

void iQuery2 (DATA d, int n, char *output) {

    DRIVERS t;
    GList *list = getOrdDrivers(d);
    char *nome, strB[BUFSIZ];
    output[0]= '\0';
    
    while (list != NULL && n > 0) {
        t = (DRIVERS)list->data;

        if(getStatusContaD(t) != 'i'){
            nome = getNomeD(t);
            sprintf(strB, "%012d;%s;%.3f\n", getIdD(t), nome, getAvalTotalD(t)/getNumViagensD(t));
            strcat(output, strB);
            free(nome);
            n--;
        }
        list = g_list_next(list);
    }
}

void bQuery2 (DATA d, int n, char path[]) {

    FILE *result = fopen(path, "w");

    DRIVERS t;
    GList *list = getOrdDrivers(d);
    char *nome;

    while (list != NULL && n > 0) {
        t = (DRIVERS)list->data;

        if(getStatusContaD(t) != 'i'){
            nome = getNomeD(t);
            fprintf(result,"%012d;%s;%.3f\n", getIdD(t), nome, getAvalTotalD(t)/getNumViagensD(t));
            free(nome);
            n--;
        }
        list = g_list_next(list);
    }

    fclose(result);
}