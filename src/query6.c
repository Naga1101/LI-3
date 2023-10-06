#include "query.h"
#include "datastruc.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *iQuery6(DATA d, char city[], char *inicio, char *fim) {
    double r = 0;
    int i = convDataToDias(inicio);
    int f = convDataToDias(fim);
    RIDES t;
    GList *list = g_list_first(lookUpCityRides(city, d));
    char *output = (char*)malloc(51);
    if (list == NULL) return output;

    int c = 0;
    while (list != NULL && getDateR((RIDES)list->data) < i)
        list = g_list_next(list);
    
    while (list != NULL && getDateR((RIDES)list->data) <= f) {
        t = (RIDES)list->data;
        r += getDistanceR(t); 
        list = g_list_next(list);
        c++;
    }

    if (r != 0) sprintf(output, "%.3f\n", r/c);
    return output;
}

void bQuery6(DATA d, char city[], int i, int f, char path[]) {
    FILE *result = fopen(path, "w");

    double r = 0;
    RIDES t;
    GList *list = g_list_first(lookUpCityRides(city, d));
    if (list == NULL) return;

    int c = 0;
    while (list != NULL && getDateR((RIDES)list->data) < i)
        list = g_list_next(list);
    
    while (list != NULL && getDateR((RIDES)list->data) <= f) {
        t = (RIDES)list->data;
        r += getDistanceR(t); 
        list = g_list_next(list);
        c++;
    }

    if (r != 0) fprintf(result, "%.3f\n", r/c);

    fclose(result);

}