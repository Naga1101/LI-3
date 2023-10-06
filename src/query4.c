#include "query.h"
#include "datastruc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *iQuery4(DATA d, char city[]) {
    double r = 0;
    RIDES t;
    GList *list = g_list_first(lookUpCityRides(city, d));
    char *output = (char*)malloc(51);
    
    int c = 0;
    while (list != NULL) {
        t = (RIDES)list->data;
        r += getCostR(t); 
        list = g_list_next(list);
        c++;
    }

    if (r != 0) sprintf(output, "%.3f\n", r/c);
    return output;
}

void bQuery4(DATA d, char city[], char path[]) {
    FILE *result = fopen(path, "w");

    double r = 0;
    RIDES t;
    GList *list = g_list_first(lookUpCityRides(city, d));

    int c = 0;
    while (list != NULL) {
        t = (RIDES)list->data;
        r += getCostR(t); 
        list = g_list_next(list);
        c++;
    }
    
    if (r != 0) fprintf(result,"%.3f\n", r/c);

    fclose(result);
    
}