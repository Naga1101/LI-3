#include "query.h"
#include "datastruc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iQuery7(DATA d, int n, char city[], char *output) {
    DriverPC dpc;
    DRIVERS t;
    char *nome, strB[BUFSIZ];
    output[0]='\0';
    GList *list = g_list_first(lookUpTopDrivRides(city, d));
    if (list == NULL) return;

    while (list != NULL && n > 0) {
        dpc = (DriverPC)list->data;
        t = getDriver(dpc);

        if(getStatusContaD(t) != 'i'){
            nome = getNomeD(t);
            sprintf(strB, "%012d;%s;%.3f\n", getIdD(t), nome, getTotalScoreDPC(dpc)/getNumRidesDPC(dpc));
            strcat(output, strB);
            free(nome);
            n--;
        }
        list = g_list_next(list);
    }
    
}

void bQuery7(DATA d, int n , char city[], char path[]) {
    FILE *result = fopen(path, "w");
    
    DriverPC dpc;
    DRIVERS t;
    char *nome;
    GList *list = g_list_first(lookUpTopDrivRides(city, d));
    if (list == NULL) return;

    while (list != NULL && n > 0) {
        dpc = (DriverPC)list->data;
        t = getDriver(dpc);

        if(getStatusContaD(t) != 'i'){
            nome = getNomeD(t);
            fprintf(result,"%012d;%s;%.3f\n", getIdD(t), nome, getTotalScoreDPC(dpc)/getNumRidesDPC(dpc));
            free(nome);
            n--;
        }
        list = g_list_next(list);
    }

    fclose(result);
}