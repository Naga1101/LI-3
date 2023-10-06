#include "query.h"
#include "datastruc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

char *iQuery1 (DATA d, char id[]){
    char *output = NULL;
    if(id[0] < '0' || id[0] > '9'){
        USERS t;
        t = lookUpUser(id, d);

        if(t != NULL && getStatusContaU(t) != 'i'){
            char *nome = getNomeU(t);
            int length = snprintf(NULL, 0, "%s;%c;%d;%.3f;%d;%.3f\n", nome, getGeneroU(t), getIdadeU(t), (getAvalTotalU(t))/(getNumViagensU(t)),getNumViagensU(t), (getTotalGastoU(t))+(getTipsDadasU(t)));
            output = (char*)malloc(length + 1);
            snprintf(output, length + 1, "%s;%c;%d;%.3f;%d;%.3f\n", nome, getGeneroU(t), getIdadeU(t), (getAvalTotalU(t))/(getNumViagensU(t)),getNumViagensU(t), (getTotalGastoU(t))+(getTipsDadasU(t)));
            free(nome);
        }
    } 
    else if(id[0] >= '0' || id[0] <= '9'){
        DRIVERS t;
        t = lookUpDriver(atoi(id), d);
        
        if(t != NULL && getStatusContaD(t) != 'i'){
            char *nome = getNomeD(t);
            int length = snprintf(NULL, 0, "%s;%c;%d;%.3f;%d;%.3f\n", nome, getGeneroD(t), getIdadeD(t), (getAvalTotalD(t))/(getNumViagensD(t)), getNumViagensD(t), (getTotalGanhoD(t))+(getTipsRecebidasD(t)));
            output = (char*)malloc(length + 1);
            snprintf(output, length + 1, "%s;%c;%d;%.3f;%d;%.3f\n", nome, getGeneroD(t), getIdadeD(t), (getAvalTotalD(t))/(getNumViagensD(t)), getNumViagensD(t), (getTotalGanhoD(t))+(getTipsRecebidasD(t)));
            free(nome);
        }
    }
    return output;
}

void bQuery1 (DATA d, char id[], char path[]){
    FILE *result;
    result = fopen(path, "w");

    if(id[0] < '0' || id[0] > '9'){
        USERS t;
        t = lookUpUser(id, d);

        if(t != NULL && getStatusContaU(t) != 'i'){
            char *nome = getNomeU(t);
            fprintf(result,"%s;%c;%d;%.3f;%d;%.3f\n", nome, getGeneroU(t), getIdadeU(t), (getAvalTotalU(t))/(getNumViagensU(t)),getNumViagensU(t), (getTotalGastoU(t))+(getTipsDadasU(t)));
            free(nome);
        }
    } 
    else if(id[0] >= '0' || id[0] <= '9'){
        DRIVERS t;
        t = lookUpDriver(atoi(id), d);

        if(t != NULL && getStatusContaD(t) != 'i'){
            char *nome = getNomeD(t);
            fprintf(result,"%s;%c;%d;%.3f;%d;%.3f\n", nome, getGeneroD(t), getIdadeD(t), (getAvalTotalD(t))/(getNumViagensD(t)), getNumViagensD(t), (getTotalGanhoD(t))+(getTipsRecebidasD(t)));
            free(nome);
        }
    }

        fclose(result);  
}