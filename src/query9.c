#include "query.h"
#include "datastruc.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iQuery9(DATA d, char *inicio, char *fim, char *output) {
    RIDES t;
    int i = convDataToDias(inicio);
    int f = convDataToDias(fim);
    GList *list = g_list_first(getRides(d));
    GList *dateList = NULL;

    while (list != NULL && getDateR((RIDES)list->data) <= i)
        list = g_list_next(list);
   
    while (list != NULL && getDateR((RIDES)list->data) <= f) {
        t = (RIDES)list->data;
        dateList = g_list_prepend(dateList, t);
        
        list = g_list_next(list);
    }
    dateList = g_list_sort(dateList, depenDistRides);

    char *date;
    char strB[BUFSIZ];
    output[0]='\0';
    int c = 0;
    while (dateList != NULL) {
        t = (RIDES)dateList->data;

        if (getTipR(t) > 0) {
            date = convDiasToData(getDateR(t));
            sprintf(strB, "%012d;%s;%d;%s;%.3f\n", getIdR(t), date, (int)getDistanceR(t), getCityR(t), getTipR(t));
            strcat(output, strB);
            free(date);
            c++;
        }
        
        dateList = g_list_next(dateList);
    }
    g_list_free(dateList);
    return c;
}

void bQuery9(DATA d, int i, int f, char path[]) {
    FILE *result = fopen(path, "w");

    RIDES t;
    GList *list = g_list_first(getRides(d));
    GList *dateList = NULL;

    while (list != NULL && getDateR((RIDES)list->data) < i)
        list = g_list_next(list);
   
    while (list != NULL && getDateR((RIDES)list->data) <= f) {
        t = (RIDES)list->data;
        dateList = g_list_prepend(dateList, t);
        
        list = g_list_next(list);
    }
    dateList = g_list_sort(dateList, depenDistRides);

    char *date;
    while (dateList != NULL) {
        t = (RIDES)dateList->data;
      
        if (getTipR(t) > 0){
            date = convDiasToData(getDateR(t));
            fprintf(result, "%012d;%s;%d;%s;%.3f\n", getIdR(t), date, (int)getDistanceR(t), getCityR(t), getTipR(t));
            free(date);
        }
        
        dateList = g_list_next(dateList);
    }
    g_list_free(dateList);

    fclose(result);
    
}