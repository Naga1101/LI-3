#include "query.h"
#include "datastruc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iQuery8(DATA d, char g, int age, char *output) {
    RIDES t;
    GList *list = g_list_first(getRides(d));
    GList *gender = NULL;
    output[0]='\0';

    while (list != NULL) {
        t = (RIDES)list->data;

        if(getGeneroU(getUserR(t)) == getGeneroD(getDriverR(t)) && getGeneroD(getDriverR(t)) == g && getIdadePerfilD(getDriverR(t)) >= age && getIdadePerfilU(getUserR(t)) >= age)
            if (getStatusContaU(getUserR(t)) == 'a' && getStatusContaD(getDriverR(t)))
                gender = g_list_prepend(gender, t);
        
        list = g_list_next(list);
    }
    
    gender = g_list_sort(gender, depenGenderRides);

    char *nameD, *username, *nameU, strB[BUFSIZ];
    int c = 0;
    while (gender != NULL) {
        t = (RIDES)gender->data;

        nameD = getNomeD(getDriverR(t));
        username = getUsernameU(getUserR(t));
        nameU = getNomeU(getUserR(t));
        sprintf(strB, "%012d;%s;%s;%s\n", getIdD(getDriverR(t)), nameD, username, nameU);
        strcat(output, strB);
        free(nameD);
        free(username);
        free(nameU);

        gender = g_list_next(gender);
        c++;
    }
    g_list_free(gender);
    return c;
}

void bQuery8(DATA d, char g, int age, char path[]) {
    FILE *result = fopen(path, "w");

    RIDES t;
    GList *list = g_list_first(getRides(d));
    GList *gender = NULL;

    while (list != NULL) {
        t = (RIDES)list->data;

        if(getGeneroU(getUserR(t)) == getGeneroD(getDriverR(t)) && getGeneroD(getDriverR(t)) == g && getIdadePerfilD(getDriverR(t)) >= age && getIdadePerfilU(getUserR(t)) >= age)
            if (getStatusContaU(getUserR(t)) == 'a' && getStatusContaD(getDriverR(t)) == 'a')
                gender = g_list_prepend(gender, t);
        
        list = g_list_next(list);
    }
    
    gender = g_list_sort(gender, depenGenderRides);

    char *nameD, *username, *nameU;
    while (gender != NULL) {
        t = (RIDES)gender->data;

        nameD = getNomeD(getDriverR(t));
        username = getUsernameU(getUserR(t));
        nameU = getNomeU(getUserR(t));
        fprintf(result,"%012d;%s;%s;%s\n", getIdD(getDriverR(t)), nameD, username, nameU);
        free(nameD);
        free(username);
        free(nameU);

        gender = g_list_next(gender);
    }
    g_list_free(gender);

    fclose(result);
    
}